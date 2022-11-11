/*
 * lmd.c --
 *
 *      licence manager server (daemon)
 *	Operating Systems and Networks 2005 project 2
 *
 *	activity is logged to syslog
 *
 *	solution heavily inspired by sample daytime server/client
 *	by prof. Schoenwaelder
 *
 *	Possible Improvements:
 *		o while wrapper arounf read()/while() in case they have to
 *		  called several times to send/receive the complete message
 *		o check protocol version sent by client
 *		o strip program name of path (for buggy clients)
 *		o add (regexp) username to licence_t structure
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <pthread.h>
#include <syslog.h>

#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MESSAGELEN 256
static const char *progname = "lmd";
/* static const char *protocol_version = "LMP/1.0"; */
static char* port = "12345"; /* default port to listen */

pthread_mutex_t licence_mutex; /*mutex for accessing shared variable licences*/
struct licence_t {
    char* program;
    int count;
}; /* we might want to add a regexp for username */

/* licence pool */
struct licence_t licences[] = {
    { "emacs",	1 },
    { "vi",	2 },
    { "bash",	3 },
};

/*
 * Create a listening TCP endpoint. First get the list of potential
 * network layter addresses and transport layer port numbers. Iterate
 * through the returned address list until an attempt to create a
 * listening TCP endpoint is successful (or no other alternative
 * exists).
 */

static int
tcp_listen(char *port)
{
    struct addrinfo hints, *ai_list, *ai;
    int n, fd = 0, on = 1;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    n = getaddrinfo(NULL, port, &hints, &ai_list);
    if (n) {
        fprintf(stderr, "%s: getaddrinfo failed: %s\n",
                progname, gai_strerror(n));
        return -1;
    }

    for (ai = ai_list; ai; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd < 0) {
            continue;
        }

        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(fd, ai->ai_addr, ai->ai_addrlen) == 0) {
            break;
        }
        close(fd);
    }

    freeaddrinfo(ai_list);

    if (ai == NULL) {
        fprintf(stderr, "%s: bind failed for port %s\n",
                progname, port);
        return -1;
    }

    if (listen(fd, 42) < 0) {
        fprintf(stderr, "%s: listen failed: %s\n",
                progname, strerror(errno));
	close(fd);
        return -1;
    }

    return fd;
}

/*
 * Accept a new TCP connection and write a message about who was
 * accepted to the system log.
 */

static int
tcp_accept(int listen)
{
    struct sockaddr_storage ss;
    socklen_t ss_len = sizeof(ss);
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    int n, fd;

    fd = accept(listen, (struct sockaddr *) &ss, &ss_len);
    if (fd == -1) {
        syslog(LOG_ERR, "accept failed: %s", strerror(errno));
        return -1;
    }

    n = getnameinfo((struct sockaddr *) &ss, ss_len,
                    host, sizeof(host), serv, sizeof(serv),
                    NI_NUMERICHOST);
    if (n) {
        syslog(LOG_ERR, "getnameinfo failed: %s", gai_strerror(n));
    } else {
        syslog(LOG_DEBUG, "connection from %s:%s", host, serv);
    }

    return fd;
}

/*
 * Close a TCP connection. This function trivially calls close() on
 * POSIX systems, but might be more complicated on other systems.
 */

static int
tcp_close(int fd)
{
    return close(fd);
}

/*
 * Parses a client GET/PUT request and fills in the variables
 * on success returns 0
 * message MUST be \0 terminated
 */
static int
parse_request(char* message, char** command, char** program, char** username,
	      char** client_protocol_version)
{
    int pos;
    
    *command = "";
    *program = "";
    *username = "";
    *client_protocol_version = "";
    
    if (strncmp(message,"GET ",4) || strncmp(message,"PUT ",4)) {
	*command = message;
	(*command)[3] = '\0';
	pos = 4;
    } else {
	return -1;
    }

    *program = &(message[pos]);
    while (message[pos] != ' ' && message[pos] != '\n'
	   && message[pos] != '\r' && message[pos] != '\0') {
	pos++;
    }
    if (message[pos] == ' ') {
	message[pos] = '\0';
	pos++;
	*username = &(message[pos]);
    }
    
    while (message[pos] != ' ' && message[pos] != '\n'
	   && message[pos] != '\r' && message[pos] != '\0') {
	pos++;
    }
    if (message[pos] == ' ') {
	message[pos] = '\0';
	pos++;
	*client_protocol_version = &(message[pos]);
    }
    while (message[pos] != ' ' && message[pos] != '\n'
	   && message[pos] != '\r' && message[pos] != '\0') {
	pos++;
    }
    if (message[pos] != '\0') {
	message[pos] = '\0';
    }
    return 0;
}

/*
 * Searches the licences structure array for program and returns an index
 * into the licence array
 * on error returns -1
 */
static int
locate_program_licence_index(char* program)
{
    int i;

    for(i=0;i<sizeof(licences)/sizeof(struct licence_t);i++) {
	if (strcmp(program,licences[i].program) == 0) {
	    return i;
	}
    }
    return -1;
}

/*
 * Waits for client to request licence, if possible gives out a licence from
 * pool and waits for client to return it. If client disconnects, licence is
 * returned to the pool as well.
 *
 * param should be a file descriptor for open socket
 */
static void*
handle_licence_request(void *param)
{
    int fd = (int) param;
    int n; /* used for checking read()/write() system calls return values */
    char message[MESSAGELEN]; /* first request message
			       * this should NOT be overwritten as program
			       * and username variables are pointers to it
			       */
    char message2[MESSAGELEN];
    int code = 400; /* code returned to client */
    char* message_text; /* human-readable message sent with the reply code */
    int licence_i = 0; /* licence index in licence structure array */
    int licence_given_out = 0; /* if licence has been given out to client */
    /* variables for first command (GET) sent by client */
    char* command = "";
    char* program = "";
    char* username = "";
    char* client_protocol_version = "";
    /* variables for second command (PUT) sent by client */
    char* program2 = "";
    char* username2 = "";
    char* client_protocol_version2 = "";
    
    /* proccess (GET) request (give out a licence) */
    /* get request */
    n = read(fd, message, sizeof(message) - 1);
    message[n] = '\0';
    
    if (parse_request(message, &command, &program, &username,
		      &client_protocol_version)) {
	/* failed to parse request */
	code = 400;
	tcp_close(fd);
	return NULL;
    }
    
    if (strcmp(command,"GET") == 0) {
	licence_i = locate_program_licence_index(program);
	if (licence_i == -1) {
	    /* program not found in licence pool */
	    code = 402;
	} else {
	    pthread_mutex_lock(&licence_mutex);
	    if (licences[licence_i].count > 0) {
		/* give out a licence */
		licences[licence_i].count--;
		code = 200;
		licence_given_out = 1;
		syslog(LOG_DEBUG,
		       "licence request granted for program %s, user %s",
		       program, username);
	    } else {
		/* no more licence left in pool */
		code = 401;
	    }
	    pthread_mutex_unlock(&licence_mutex);
	}
    }

    /* prepare human-redable text for repsonse */
    switch (code) {
    case 200:
	message_text = "OK";
	break;
    case 401:
	message_text = "no licences left";
	break;
    case 402:
	message_text = "unknown program name";
	break;
    default:
	message_text = "unknown error";
	break;
    }
    snprintf(message2,sizeof(message2),"%d %s\r\n", code, message_text);

    /* send response to client */
    n = write(fd, message2, strlen(message2));
    if (n != strlen(message2)) {
        fprintf(stderr, "%s: write failed\n", progname);
    }
    
    /* continue only if we gave out a licence */
    if (code != 200) {
	tcp_close(fd);
	return NULL;
    }


    /* process (PUT) request or client disconnect (return licence to pool) */
    /* get request */
    n = read(fd, message2, sizeof(message2) - 1);
    message2[n] = '\0';
    
    code = 400;
    if (parse_request(message2, &command, &program2, &username2,
		      &client_protocol_version2)) {
	/* failed to parse request */
	code = 400;
	tcp_close(fd);
	return NULL;
    }

    if (strcmp(command,"PUT") == 0) {
	if (strcmp(program,program2)==0 && strcmp(username,username2)==0) {
	    if (licence_given_out) {
		/* return a licence only if we gave it out */
		pthread_mutex_lock(&licence_mutex);
		licences[licence_i].count++;
		syslog(LOG_DEBUG,
		       "licence returned for program %s, user %s",
		       program, username);
		pthread_mutex_unlock(&licence_mutex);
		code = 200;
		licence_given_out = 0;
	    }
	} else {
	    /* program or username do not match */
	    code = 403;
	}
    } 

    switch (code) {
    case 200:
	message_text = "OK";
	break;
    case 403:
	message_text = "program name or user name mismatch";
	break;
    default:
	message_text = "unknown error";
	break;
    }
    snprintf(message2,sizeof(message2),"%d %s\r\n", code, message_text);

    /* send response to client */
    n = write(fd, message2, strlen(message2));
    if (n != strlen(message2)) {
        fprintf(stderr, "%s: write failed\n", progname);
    }
    tcp_close(fd);
    
    if (licence_given_out) {
	/* if client disconnected or for any other reason the licence has
	 * still not been returned to the pool, return it now
	 */
	pthread_mutex_lock(&licence_mutex);
	licences[licence_i].count++;
	syslog(LOG_DEBUG,
	       "client misbehaving! returning licence for program %s, user %s",
	       program, username);
	pthread_mutex_unlock(&licence_mutex);
    }
    return NULL;
}

static void
usage()
{
    fprintf(stderr, "Usage: %s [-p port]\n", progname);
}

int
main(int argc, char *argv[])
{
    int tfd; /* socket we are listening on */
    int fd; /* open socket after accept */
    int err;
    pthread_t th;
    char c;
    
    /* parse arguments */
    while ((c = getopt(argc, argv, "p:")) >= 0) {
        switch (c) {
        case 'p':
	    port = optarg;
            break;
        case ':':
        case '?':
	    usage();
            exit(EXIT_FAILURE);
        }
    }
    if (argc != optind) {
	usage();
        exit(EXIT_FAILURE);
    }           

    openlog(progname, LOG_PID, LOG_DAEMON);
    pthread_mutex_init(&licence_mutex, NULL);
    tfd = tcp_listen(port);

    while (tfd != -1) {
	fd = tcp_accept(tfd);
	err = pthread_create(&th, NULL, handle_licence_request, (void*) fd);
	if ( err != 0) {
	    fprintf(stderr, "%s: %s: unable to handle_licence thread: %d\n",
		    progname, __func__, err);
	    continue;
	}
	pthread_detach(th);
    }

    tcp_close(tfd);
    closelog();
    pthread_mutex_destroy(&licence_mutex);

    return EXIT_SUCCESS;
}
