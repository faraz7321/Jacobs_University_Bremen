#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

void error(char* msg){
		perror(msg);
		exit(1);
}

int main(int argc, char *argv[]){
	if(argc<2){
			fprintf(stderr,"No port provided\n");
			exit(1);
	}	
	int sockfd, newsockfd, portno, n;	//File descriptor for Sockets
	char buffer[255];	//Temporary buffer to read and write data
	
	struct sockaddr_in serv_addr,cli_addr;	//Structure to hold Server and Client details
	socklen_t cli_len;	//Client length 
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	//AF_INET refers to addresses from the internet, IP addresses specifically. SOCK_STREAM to refer TCP(SOCK_DGRAM for UDP), 0 again for TCP
	if(sockfd<0){
			error("Socket failed \n");
	}
	bzero((char*) &serv_addr,sizeof(serv_addr));	//The bzero() function shall place n zero-valued bytes in the area pointed to by s.
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;	//INADDR_ANY is used when you don't need to bind a socket to a specific IP. When you use this value as the address when calling bind() , the socket accepts connections to all the IPs of the machine.
	serv_addr.sin_port = htons(portno);	//the htons() function converts values between host and network byte orders. There is a difference between big-endian and little-endian and network byte order depending on your machine and network protocol in use.
	
	if(bind(sockfd, (struct sockaddr*) &serv_addr,sizeof(serv_addr))<0){	//Binding the socket
		error("Binding failed\n");
	}
	
	listen(sockfd, 5);//Listening for new Connections
	cli_len = sizeof(cli_addr);
	
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &cli_len);//Accept the new connection
	
	if(newsockfd<0)
		error("error accepting new connection \n");
	
	while(1){
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);	//Read incoming data streams
		if(n<0)
			error("Error reading from Client");
		printf("Client : %s \n", buffer);
		bzero(buffer, 255);
		printf("Server :");
		fgets(buffer, 255, stdin);
		n = write(newsockfd, buffer, strlen(buffer));
		if(n<0)
			error("Error writing to server\n");
		if(strncmp(buffer, "Bye", 3) == 0)
			break;
	}
	
	close(sockfd);
	close(newsockfd);
	return 0;
}
