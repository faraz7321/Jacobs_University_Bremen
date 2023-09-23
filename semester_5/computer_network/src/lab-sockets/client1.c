#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>	//For gethostbyname function

void error(char* msg){
		perror(msg);
		exit(1);
}

int main(int argc, char *argv[]){
	if(argc<3){
			fprintf(stderr,"No port provided\n");
			exit(1);
	}	
	int sockfd, portno, n;	//File descriptor for Sockets
	char buffer[255];	//Temporary buffer to read and write data
	
	struct sockaddr_in serv_addr;	//Structure to hold Server and Client details
	struct hostent* server;
	
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	//AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_STREAM to refer TCP(SOCK_DGRAM for UDP), 0 again for TCP
	if(sockfd<0){
			error("Socket failed \n");
	}
	
	server = gethostbyname(argv[1]);	//Resolving the host server and storing its details
	if(server == NULL){
		error("No such host\n");
	}
	
	bzero((char*) &serv_addr, sizeof(serv_addr));	//Empty contents of serv_addr
	serv_addr.sin_family = AF_INET;	//Assign IPv4 family to server_address
	bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);	//Copy contents of host server address resolved into serv_addr
	serv_addr.sin_port = htons(portno);
	
	if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)	//Connecting to Server
		error("Connection failed\n");
	
	while(1){
		bzero(buffer, 256);
		printf("Me: ");
		fgets(buffer, 255, stdin);
		n = write(sockfd, buffer, strlen(buffer));	//Write to server
		if(n<0)
			error("Error writing to server\n");
		n = read(sockfd, buffer, 255);	//Read incoming data streams
		if(n<0)
			error("Error reading from Server");
		printf("Server : %s \n", buffer);
		if(strncmp(buffer, "Bye", 3) == 0)
			break;
	}
	
	return 0;
}
