/*
 * Name: Stephen Tambussi
 * Date: 2/11/2021
 * Title: Lab 6 - Stop and Wait for an Unreliable Channel with Loss
 * Description: Similar to lab5, this program implements the Stop and Wait protocol
 * version 3 with packet loss correction over UDP.
 */
#include "lab6.h"
int sequence;

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;
    while (ptr < end) {
        checksum ^= *ptr;
	ptr++;
    } 
        return checksum;
}

void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {
    while (1) {
        //if retries is greater than 3, we give up and move on
	    if(retries>=3){
		    break;
	    }
        // calculate the checksum
        packet.header.cksum = getChecksum(packet);
        
        // Print what is being sent
        printf("Created: ");
        printPacket(packet);

        // Simulate lost packet.
        if (rand() % PLOSTMSG == 0) {
            printf("Dropping packet\n");
        } else {
            sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
        }

        // wait until an ACK is received or timeout using select statement
        // recall recvfrom() is a blocking function, i.e. blocks until data is available
        // so what if data from server got lost, so select() solves this problem. type man select for more information.

        struct timeval tv; //structure to hold timeout length
        tv.tv_sec = 0;
        tv.tv_usec = 500000;//half a second
        int rv;
        //setup select parameters
        fd_set readfds; //set of file descriptors to be checked
        fcntl(sockfd,F_SETFL,O_NONBLOCK);
        //start before calling select
        FD_ZERO(&readfds); //clears the fd_set
        FD_SET(sockfd,&readfds); //adds sockfd to fd_set
        //call select. sockfd+1 is used because select checks upto sockfd-1 descriptors.
        rv=select(sockfd+1,&readfds,NULL,NULL,&tv);
        if(rv==0){ // no data has been received
            printf("Timeout\n");
            //increment retries if packet is dropped
            retries++;
        }
        else{ //if rv!=0, there is something to receive
		    printf("**%i SOCKET(S) READY**\n", rv);
    
        	// receive an ACK from the server
        	Packet recvpacket;
        	recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, (struct sockaddr *)address, &addrlen);

        	// print what was received
        	printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

        	// validate the ACK
        	if (recvpacket.header.cksum != getChecksum(recvpacket)) {
            	// bad checksum, resend packet
            		printf("Bad checksum, expected %d\n", getChecksum(recvpacket));
        	} else if (recvpacket.header.seq_ack != sequence) {
            	// incorrect sequence number, resend packet
            		printf("Bad seqnum, expected %d\n", packet.header.seq_ack);
        	} else {
            	// good ACK, we're done
			    (sequence == 0) ? (sequence = 1) : (sequence = 0);
            		printf("Good ACK\n");
            		break;
        	}
    	}
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int sockfd;
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	    perror("Failure to setup an endpoint socket.");
	    exit(1);
    }

    // initialize the server address structure
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    struct hostent *host;
    host = (struct hostent *)gethostbyname(argv[1]);
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2])); //port number
    address.sin_addr = *((struct in_addr *)host->h_addr); //IP address
    // open file
    FILE *file = fopen(argv[3], "rb");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // send file contents to server
    Packet packet;
    int b_read;
    sequence = 0;
    while(1)
    {
	    b_read = fread(packet.data, 1, sizeof(packet.data), file);
	    if(b_read == 0) break; //reads and transmits data in file until there is no more data in the file
	    packet.header.seq_ack = sequence;
	    packet.header.len = b_read;
	    ClientSend(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr), packet, 0);
    }

    // send zero-length packet to server to end connection according the description provided in the Lab manual
    packet.header.seq_ack = sequence;
    packet.header.len = 0;
    packet.header.cksum = getChecksum(packet);
    ClientSend(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr), packet, 0);

    // clean up
    if(fclose(file) != 0)
    {
	    perror("Error closing file.");
	    exit(1);
    }
    close(sockfd);
    return 0;
}
