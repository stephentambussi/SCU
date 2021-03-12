//UDP Client - run this on client computer
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#define BUF_SIZE 1024
#define NET_SIZE 32

int main()
{
	int sockfd;
	char sbuf[BUF_SIZE];
	char rbuf[BUF_SIZE];
	char net_buf[NET_SIZE];
	struct sockaddr_in servAddr;
	struct hostent *host;
	FILE *fp;
	host = (struct hostent *)gethostbyname("localhost");

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Failure to setup an endpoint socket");
		exit(1);
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(5000);
	servAddr.sin_addr.s_addr = INADDR_ANY;
	int len, n;

	while(1)
	{
		printf("Type a message to send to Server \n");
		printf("Client: ");
		gets(sbuf); //reads into buffer msg to be sent
		sendto(sockfd, sbuf, strlen(sbuf), MSG_CONFIRM, (struct sockaddr *)&servAddr, sizeof(struct sockaddr));
		n = recvfrom(sockfd, rbuf, BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&servAddr, &len);
		rbuf[n] = '\0';
		printf("Server responded: %s\n", rbuf);
		if(!(strcmp(rbuf, "File sent.")))
		{
			fp = fopen("clone.txt", "w");//opens file with name clone.txt
			if(fp == NULL) printf("Error opening file.\n");
			while(1)
			{
				recvfrom(sockfd, net_buf, NET_SIZE, MSG_WAITALL, (struct sockaddr *)&servAddr, &len);
				if(!(strcmp(net_buf, "Empty.")))
					break;
				fwrite(net_buf, 1, NET_SIZE, fp);
				memset(net_buf, 0, NET_SIZE*sizeof(net_buf));
			}
			fclose(fp);
		}

	}
	return 0;
}
