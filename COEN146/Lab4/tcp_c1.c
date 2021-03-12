/*
 * Name: Stephen Tambussi
 * Date: 1/28/2021
 * Title: Lab4 - Step 1
 * Description: This program provides the client side connection
 * using TCP to transfer a file
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#define BUF_SIZE 1024
#define NET_SIZE 32

int main()
{
	int sockfd;
	int flag = 0;
	char sbuf[BUF_SIZE];
	char rbuf[BUF_SIZE];
	char net_buf[NET_SIZE];
	struct sockaddr_in servAddr;
	struct hostent *host;
	FILE *fp;
	host = (struct hostent *)gethostbyname("localhost");//loopback address

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)//opens a socket 
	{
		perror("Failure to setup an endpoint socket\n");
		exit(1);
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(5000);
	servAddr.sin_addr.s_addr = INADDR_ANY;
	int len, n;

	//initiate connection to the server
	if(connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr)))
	{
		perror("Failure to connect to the server\n");
		exit(1);
	}

	while(1)
	{
		printf("Type a message to send to Server \n");
		printf("Client: ");
		bzero(sbuf, BUF_SIZE);//zeroes buffer to start fresh
		gets(sbuf); //reads into buffer msg to be sent
		n = send(sockfd, sbuf, BUF_SIZE, 0);//sends data in send buffer to server
		if (n < 0) perror("ERROR writing to socket.\n");
		bzero(rbuf, BUF_SIZE);
		n = recv(sockfd, rbuf, BUF_SIZE, 0);//receives data server sent back
		if (n < 0) perror("ERROR reading from socket.\n");
		rbuf[n] = '\0';
		printf("Server responded: %s\n", rbuf);
		if(!(strcmp(rbuf, "File sent.")))//begins process of receiving file
		{
			fp = fopen("clone.txt", "w");//opens file with name clone.txt
			if(fp == NULL) printf("Error opening file.\n");
			while(1)
			{
				n = recv(sockfd, net_buf, NET_SIZE, 0);//starts receiving data from file
				if (n < 0) perror("ERROR reading from socket.\n");
				if(n == 0)
				{
					flag = 1;
					break;
				}
				fwrite(net_buf, 1, n, fp);//writes the data from server onto the local machine
				memset(net_buf, 0, n);//clears the buffer
			}
			fclose(fp);
		}
		if(flag == 1)
			break;
	}
	close(sockfd);
	return 0;
}
