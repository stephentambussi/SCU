//UDP server - run this on server computer
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#define BUF_SIZE 1024
#define NET_SIZE 32

int main()
{
	int sockfd, b_read;
	char rbuf[BUF_SIZE];
	char net_buf1[NET_SIZE];
	char *response = "I am fine.";
	char *response2 = "File sent.";
	char *file_empty = "Empty.";
	struct sockaddr_in servAddr, clienAddr;
	socklen_t addrLen = sizeof(struct sockaddr);
	time_t rawtime;
	struct tm* timeinfo;
	FILE *fp;
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
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
	
	while(1)
	{
		printf("Server waiting for messages from client. \n");
		int nr = recvfrom(sockfd, rbuf, BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&clienAddr, &addrLen);
		rbuf[nr] = '\0';
		if(!(strcmp(rbuf, "How are you?")) || !(strcmp(rbuf, "how are you?")))
		{
			sendto(sockfd, (const char *)response, strlen(response), MSG_CONFIRM, (struct sockaddr *)&clienAddr, sizeof(clienAddr));
		}
		else if(!(strcmp(rbuf, "What is the time?")) || !(strcmp(rbuf, "what is the time?")) || !(strcmp(rbuf, "What's the time?")))
		{
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			sendto(sockfd, asctime(timeinfo), strlen(asctime(timeinfo)), MSG_CONFIRM, (struct sockaddr *)&clienAddr, sizeof(clienAddr));
		}
		else if(!(strcmp(rbuf, "Send me a file")) || !(strcmp(rbuf, "send me a file")))
		{
			sendto(sockfd, (const char *)response2, strlen(response), MSG_CONFIRM, (struct sockaddr *)&clienAddr, sizeof(clienAddr));
			fp = fopen("Bible.txt", "r");//opens file to read
			if(fp == NULL) printf("Can't open file. \n");
			while(1)
			{
				b_read = fread(net_buf1, 1, NET_SIZE, fp);
				if(b_read == 0)
				{
					sendto(sockfd, (const char *)file_empty, strlen(file_empty), MSG_CONFIRM, (struct sockaddr *)&clienAddr, sizeof(clienAddr));
					break;
				}
				sendto(sockfd, net_buf1, sizeof(net_buf1), MSG_CONFIRM, (struct sockaddr *)&clienAddr, sizeof(clienAddr));//sends file data over network
				memset(net_buf1, 0, NET_SIZE*sizeof(net_buf1));//clears buffer after data is transmitted 	
			}
			fclose(fp);
		}
	}
	return 0;
}
