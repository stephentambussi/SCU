/*
 * Name: Stephen Tambussi
 * Date: 2/4/2021
 * Title: Lab 5 - Stop and Wait for an Unreliable Channel
 * Description: This program implements the Stop and Wait protocol
 * on UDP to provide reliable data transfer
 */
#include "lab5.h"

int sequence;

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;

    int checksum = 0;
    char *ptr = (char *)&packet;//points to the address of struct packet
    char *end = ptr + sizeof(Header) + packet.header.len;

    while (ptr < end) {
        checksum ^= *ptr;//gets address and xors it
	ptr++;//goes to next location in memory
    }

    return checksum;
}

// printPacket()
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}


//clientSend()
void clientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet) {
    while (1) {
	//packet.header.cksum = getChecksum(packet);
	//Introduce random number generator to mimic bad packet sending to test rdt
	int rn = rand() % 4;//generate random number to error check checksum
	printf("rand num: %d \n", rn);
	if(rn > 2)
		packet.header.cksum = 7;//set cksum to 7 when it is another num
	else
		packet.header.cksum = getChecksum(packet);//correct checksum
	rn = rand() % 4; //generate another random number to error check sequence num
	printf("rand num: %d \n", rn);
	if(rn > 2)
		packet.header.seq_ack = !sequence;
	else 
		packet.header.seq_ack = sequence;
        // send the packet
        printf("Client: sending packet\n");
	sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);		
        // receive an ACK from the server
        Packet recvpacket;
	recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, (struct sockaddr *)address, &addrlen);
        // log what was received
        printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

        //print received packet
	printPacket(recvpacket);
        // validate the ACK
        if (recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Bad checksum, expected checksum was: %d\n", getChecksum(recvpacket));
        } else if (recvpacket.header.seq_ack != sequence) {
            // incorrect sequence number, resend packet
            printf("Bad seqnum, expected sequence number was: %d\n", sequence);
        } else {
            // good ACK, we're done
	    (sequence == 0) ? (sequence = 1) : (sequence = 0);
            printf("Good ACK\n");
            break;
        }
    }
}

int main(int argc, char *argv[]) {
	int sockfd;
	FILE *fp;
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket [name the socket sockfd] 	    
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Failure to setup an endpoint socket.");
		exit(1);
	}

    // initialize the server address structure using argv[2] and argv[1]
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    struct hostent *host;
    host = (struct hostent *)gethostbyname(argv[1]);
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[2])); //converts string arg to int
	address.sin_addr = *((struct in_addr *)host->h_addr); //converts string arg to int
    // open file using argv[3]
	fp = fopen(argv[3], "r"); //opens file to read and send data to server
	if(fp == NULL)
	{
		perror("Error opening file.");
		exit(1);
	}
    // send file contents to server
	//-create a packet
	//-set the seq_ack field 
	//-set the len field
	//-calculate the checksum
	//-send the packet
	Packet send_p;
	int b_read;
	sequence = 0;
	while(1)
	{
		b_read = fread(send_p.data, 1, sizeof(send_p.data), fp);
		if(b_read == 0)
			break;
		send_p.header.seq_ack = sequence;
		send_p.header.len = b_read;
		clientSend(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr), send_p);
	}


    // send zero-length packet to server to end connection
    	send_p.header.seq_ack = sequence;
	send_p.header.len = 0;
	send_p.header.cksum = getChecksum(send_p);
	clientSend(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr), send_p);

    // clean up
	//-close the sockets and file
	if(fclose(fp) != 0)
	{
		perror("Error closing file.");
		exit(1);
	}
	close(sockfd);
    return 0;
}
