/*
 * Name: Stephen Tambussi
 * Date: 1/28/2021
 * Title: Lab4 - Step 1
 * Description: This programs provides the server side connection
 * using TCP to send a file.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#define BUF_SIZE 1024
#define NET_SIZE 32

int main()
{
	int sockfd, connfd, b_read, flag, sin_size;
	char rbuf[BUF_SIZE];
	char net_buf1[NET_SIZE];
	char *response2 = "File sent.";
	char *file_empty = "Empty.";
	struct sockaddr_in servAddr, clienAddr;
	socklen_t addrLen = sizeof(struct sockaddr);
	FILE *fp;
	//set up the socket file descriptor
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Failure to setup an endpoint socket");
		exit(1);
	}
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(5000);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	if((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0)
	{
		perror("Failure to bind server address to the endpoint socket");
		exit(1);
	}

	listen(sockfd, 5);
	sin_size = sizeof(struct sockaddr_in);
	int nr, nw;
	flag = 0;
	while(1)
	{
		//accepts incoming connection from client
		if((connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size)) < 0)
		{
			perror("Failure to accept connection to the client.\n");
			exit(1);
		}
		printf("Connection established with client: IP %s and Port %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
		while(1)
		{
			printf("Server waiting for messages from client. \n");
			nr = recv(connfd, rbuf, BUF_SIZE, 0);//receives data from client and puts it into the receive buffer
			if(nr < 0) perror("ERROR reading from socket\n");
			rbuf[nr] = '\0';
			if(!(strcmp(rbuf, "Send me a file")) || !(strcmp(rbuf, "send me a file")))
			{
				//Sends the File sent response to client
				nw = send(connfd, (const char *)response2, strlen(response2), 0);
				if(nw < 0) perror("ERROR writing to socket\n");
				fp = fopen("Bible.txt", "r");//opens file to read
				if(fp == NULL) printf("Can't open file. \n");
				while(1)
				{
					//begins to read data from file to send to client
					b_read = fread(net_buf1, 1, NET_SIZE, fp);
					if(b_read == 0)//when there is nothing left to read in the file
						break;
					//sends file data over network
					nw = send(connfd, net_buf1, b_read, 0);
					if(nw < 0) perror("ERROR writing to socket\n");
					memset(net_buf1, 0, NET_SIZE);//clears buffer after data is transmitted 	
				}	
				close(connfd);
				fclose(fp);
				flag = 1;
			}
			if(flag == 1)
				break;
		}
		break;
	}
	close(sockfd);
	return 0;
}
