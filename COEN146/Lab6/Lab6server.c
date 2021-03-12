/*
 * Name: Stephen Tambussi
 * Date: 2/11/2021
 * Title: Lab 6 - Stop and Wait for an Unreliable Channel with Loss
 * Description: Similar to lab5, this program implements the Stop and Wait protocol
 * version 3 with packet loss correction over UDP.
 */
#include "lab6.h"

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

//print packet
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//serverSend()
void serverSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    // Simulating a chance that ACK gets lost
    if (rand() % PLOSTMSG == 0) {
        printf("Dropping ACK\n");
    }
    else{
        Packet packet;
        //prepare and send the ACK
        packet.header.seq_ack = seqnum;
	    packet.header.len = 0;
	    packet.header.cksum = getChecksum(packet);
        printf("Sent ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
	    sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
    }
}

Packet serverReceive(int sockfd, struct sockaddr *address, socklen_t *addrlen, int seqnum)
{
    Packet packet; 
    while (1) {
        //Receive a packet from the client
        recvfrom(sockfd, &packet, sizeof(packet), 0, address, addrlen);

        // print what was received
        printf("Received: ");
        printPacket(packet);

        //verify the checksum and the sequence number
        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected %d\n", getChecksum(packet));
            serverSend(sockfd, address, *addrlen, !seqnum); //repeat last ACK message if checksum or seqnum are incorrect
        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected %d\n", seqnum);
            serverSend(sockfd, address, *addrlen, !seqnum);
        } else {
            printf("Good packet\n");
            serverSend(sockfd, address, *addrlen, seqnum);
	        break;
        }
    }
    printf("\n");
    return packet;
}

int main(int argc, char *argv[]) {
    int sockfd;
    FILE *fp;
    // check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <outfile>\n", argv[0]);
        exit(1);
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create a socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	    perror("Failure to setup an endpoint socket.");
	    exit(1);
    }

    // initialize the server address structure
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[1]));
    address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
    if((bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr))) < 0)
    {
	    perror("Failure to bind server address to endpoint socket");
	    exit(1);
    }

    // open file using argv[2]
    fp = fopen(argv[2], "wb");
    if(fp == NULL)
    {
	    perror("file failed to open\n");
	    exit(1);
    }
    // get file contents from client and save it to the file
    int seqnum = 0;
    Packet packet;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    do {
        packet = serverReceive(sockfd, (struct sockaddr *)&clientaddr, &clientaddr_len, seqnum);
	    fwrite(packet.data, 1, packet.header.len, fp);
	    (seqnum == 0) ? (seqnum = 1) : (seqnum = 0);
	    //printf("packet seqnum %d | packet length %d\n", packet.header.seq_ack, packet.header.len);//for debugging
    } while (packet.header.len != 0); //once the server receives the zero-length packet it closes the connection

    //cleanup
    if(fclose(fp) != 0)
    {
	    perror("Error closing file.");
	    exit(1);
    }
    close(sockfd);
    return 0;
}
