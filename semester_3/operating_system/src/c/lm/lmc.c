/*
 * lmc.c --
 *
 *      licence manager client
 *	Operating Systems and Networks 2005 project 2
 *
 *	solution heavily inspired by sample daytime server/client
 *	by prof. Schoenwaelder
 *
 *	Possible Improvements:
 *		o while wrapper arounf read()/while() in case they have to
 *		  called several times to send/receive the complete message
 *		o check protocol version read from server
 *		o strip program name of path
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>

#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


#define MESSAGELEN 256
static const char *progname = "lmc";
static const char *protocol_version = "LMP/1.0";
static char* host = "127.0.0.1";
static char* port = "12345";


/*
 * Establish a connection to a remote TCP server. First get the list
 * of potential network layer addresses and transport layer port
 * numbers. Iterate through the returned address list until an attempt
 * to establish a TCP connection is successful (or no other
 * alternative exists).
 */

static int
tcp_connect(char *host, char *port)
{
    struct addrinfo hints, *ai_list, *ai;
    int n, fd = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    n = getaddrinfo(host, port, &hints, &ai_list);
    if (n != 0) {
        fprintf(stderr, "%s: getaddrinfo: %s\n",
                progname, gai_strerror(n));
        exit(EXIT_FAILURE);
    }

    for (ai = ai_list; ai; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd < 0) {
	    switch (errno) {
	    case EAFNOSUPPORT:
	    case EPROTONOSUPPORT:
		continue;
		
	    default:
		fprintf(stderr, "%s: socket: %s\n",
			progname, strerror(errno));
		continue;
	    }
        } else {
	    if (connect(fd, ai->ai_addr, ai->ai_addrlen) == -1) {
		close(fd);
		fprintf(stderr, "%s: connect: %s\n",
			progname, strerror(errno));
		continue;
	    }
        }
	break;	/* still here? we were successful and we are done */
    }

    freeaddrinfo(ai_list);

    if (ai == NULL) {
        fprintf(stderr, "%s: could not connect to %s port %s\n",
                progname, host, port);
        exit(EXIT_FAILURE);
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
 * Request a licence from the server
 * on success returns zero
 *
 * we might want to remove path from the program name
 */

static int
request_licence(int fd, char* program, char* username)
{
    int n;
    char message[MESSAGELEN];
    int code; /* code returned from licence server */
    int result;

    snprintf(message,MESSAGELEN, "GET %s %s %s\n",
	     program, username, protocol_version);

    /* send request */
    n = write(fd, message, strlen(message));
    if (n != strlen(message)) {
        fprintf(stderr, "%s: write failed\n", progname);
        return -1;
    }
    
    /* get answer */
    n = read(fd, message, sizeof(message) - 1);
    message[n] = '\0';
    //    printf("%s", message);
    
    if (sscanf(message,"%3d",&code) != 1) {
	fprintf(stderr, "unknown reply from server: %s\n", message);
	return -2;
    }

    switch (code) {
    case 200:
	result = 0;
	break;
    case 401:
	fprintf(stderr, "no licence left\nserver response: %s",message);
	result = 1;
	break;
    case 402:
	fprintf(stderr, "unknown program name: %s\nserver response: %s",
		program, message);
	result = 2;
	break;
    default:
	fprintf(stderr, "unknown error code %d\nserver response: %s",
		code, message);
	result = -3;
	break;
    }
    return result;
}


/*
 * Return licence to the server
 * on success returns zero
 */
static int
return_licence(int fd, char* program, char* username)
{
    int n;
    char message[MESSAGELEN];
    int code; /* code returned from licence server */
    int result;

    snprintf(message,MESSAGELEN, "PUT %s %s %s\n",
	     program, username, protocol_version);

    /* send request */
    n = write(fd, message, strlen(message));
    if (n != strlen(message)) {
        fprintf(stderr, "%s: write failed\n", progname);
        return -1;
    }
    
    /* get answer */
    n = read(fd, message, sizeof(message) - 1);
    message[n] = '\0';
    //    printf("%s", message);
    
    if (sscanf(message,"%3d",&code) != 1) {
	fprintf(stderr, "unknown reply from server: %s\n", message);
	return -2;
    }

    switch (code) {
    case 200:
	result = 0;
	break;
    default:
	fprintf(stderr, "unknown error code %d\nserver response: %s",
		code, message);
	result = -3;
	break;
    }
    return result;
}

/*
 * returns username of current user
 */
char*
whoami()
{
  register struct passwd *pw;
  register uid_t uid;

  uid = geteuid ();
  pw = getpwuid (uid);
  if (pw) {
      return pw->pw_name;
  } else {
      return "";
  }
}

static void
usage()
{
    fprintf(stderr, "Usage: %s [-h host] [-p port] program\n", progname);
}

int
main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    char **args;
    //    int i;
    int fd;
    char* username;
    char c;

    /* parse arguments */
    while ((c = getopt(argc, argv, "h:p:")) >= 0) {
        switch (c) {
        case 'h':
	    host = optarg;
            break;
        case 'p':
	    port = optarg;
            break;
        case ':':
        case '?':
	    usage();
            exit(EXIT_FAILURE);
        }
    }
    args = &(argv[optind]); /* program to execute */
    optind++;
    if (argc != optind) {
	usage();
        exit(EXIT_FAILURE);
    }           

    username = whoami();

    /* request licence */
    fd = tcp_connect(host,port);
    if (request_licence(fd, args[0], username)) {
	fprintf(stderr, "failed to obtain a licence\n");
	tcp_close(fd);
	return EXIT_FAILURE;
    }
    
    /* run client program */
    fprintf(stderr, "starting client program...\n");
    pid = fork();
    if (pid == -1) {
	perror(progname);
	return EXIT_FAILURE;
    }
    if (pid == 0) {			/* child */
	close(fd); /* we don't want to give the user process a chance
		    * to access our open socket to lmd
		    */
	execvp(args[0], args);
	perror(progname);
	_exit(EXIT_FAILURE);
    } else {				/* parent */
	fprintf(stderr, "waiting for client program to finish...\n");
	waitpid(pid, &status, 0);
	fprintf(stderr, "client program finished\n");

	/* return licence */
	if (return_licence(fd, args[0], username)) {
	    fprintf(stderr, "licence might not have been returned properly\n");
	}
	tcp_close(fd);
    }
    
    return EXIT_SUCCESS;
}
