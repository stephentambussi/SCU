/*
 * Name: Stephen Tambussi
 * Date: 3/8/2021
 * Title: Lab 7 - Link State Routing
 * Description: This program simulates the behavior of a router/node in a network
 * by implementing link state routing with Dijkstra's algorithm.
 */
 
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>


//defines
#define	N 4
#define	INFINITE 1000
#define MIN(a,b) (((a) < (b)) ? (a) : (b))


// types
typedef struct machines
{
	char name[50];
	char ip[50];
	int port;	

} MACHINES;


// global variables
MACHINES machines[N]; //array of structs 
int costs[N][N];
int distances[N];
int myid;
int sock;
struct sockaddr_in addr;
struct sockaddr_in otheraddr;
socklen_t addr_size;
pthread_mutex_t	lock;


// functions
void *run_link_state (void *);
void *receive_info (void *);
void print_costs (void);


//main()
int main (int argc, char *argv[])
{
	if (argc != 4) {
		fprintf(stderr, "usage: %s <myid> <costs> <machines>\n", argv[0]);
		exit(1);
	}
	FILE *fp;
	int i, j;
	pthread_t thr1, thr2;
	int id, cost;
	int packet[3];
	myid = atoi(argv[1]);

	// get costs
	if ((fp = fopen(argv[2], "r")) == NULL)
	{
		printf("can't open %s\n", argv[2]);
		return 1;
	}
	
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			fscanf(fp, "%d", &costs[i][j]);
		}
	}

	fclose (fp);
		

	//get info on machines 
	if ((fp = fopen (argv[3], "r")) == NULL)
	{
		printf ("can't open %s\n", argv[3]);
		return 1;
	}

	for (i = 0; i < N; i++)
		fscanf (fp, "%s%s%d", machines[i].name, machines[i].ip, &machines[i].port);

	fclose (fp);

	
    // init address
    addr.sin_family = AF_INET;
    addr.sin_port = htons ((short)machines[myid].port);
    addr.sin_addr.s_addr = htonl (INADDR_ANY);
    memset ((char *)addr.sin_zero, '\0', sizeof (addr.sin_zero));
    addr_size = sizeof (addr);

    // create socket
    if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf ("socket error\n");
        return 1;
    }

    // bind
    if (bind (sock, (struct sockaddr *)&addr, sizeof (addr)) != 0)
    {
        printf ("bind error\n");
        return 1;
    }


	// create threads
	pthread_mutex_init (&lock, NULL); //initialize mutex
	pthread_create (&thr1, NULL, receive_info, NULL);
	pthread_create (&thr2, NULL, run_link_state, NULL);

	// read changes from the keyboard
	for (i = 0; i < 3; i++)
	{
		printf ("any changes? \n");
		scanf ("%d %d", &id, &cost);//check if space is okay for formatting
		if (id >= N  ||  id == myid)
		{
			printf ("wrong id\n");
			break;
		}

		pthread_mutex_lock (&lock);
		costs[myid][id] = cost; //(i,j)
		costs[id][myid] = cost; //(j,i)
		pthread_mutex_unlock (&lock);
		print_costs ();

		packet[0] = htonl (myid);
		packet[1] = htonl (id);
		packet[2] = htonl (cost);
		otheraddr.sin_family = AF_INET;
		addr_size = sizeof (otheraddr);

		for (j = 0; j < N; j++)
		{
			if (j != myid)
			{
				otheraddr.sin_port = htons ((short)machines[j].port);
				inet_pton (AF_INET, machines[j].ip, &otheraddr.sin_addr.s_addr);
				sendto (sock, packet, sizeof (packet), 0, (struct sockaddr *)&otheraddr, addr_size);
			}
		}
		printf ("sent\n");
	}
	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	sleep (20);

}


// receive info
void *receive_info (void *arg)
{
	//Code to receive info and update costs
	int recv_packet[3];
	while(1) {
		recvfrom(sock, recv_packet, sizeof(recv_packet), 0, (struct sockaddr *)&addr, &addr_size);
		//convert back to host byte order
		recv_packet[0] = ntohl(recv_packet[0]);//id of sending host(myid)
		recv_packet[1] = ntohl(recv_packet[1]);//id of neighbor node to host id
		recv_packet[2] = ntohl(recv_packet[2]);//the updated cost between them
		printf("Local cost table updated: (%d, %d) = %d \n", recv_packet[0], recv_packet[1], recv_packet[2]);
		//packet array: [myid(i/j), id(j/i), cost(value to update at (i,j)]
		pthread_mutex_lock(&lock);
		costs[recv_packet[0]][recv_packet[1]] = recv_packet[2]; //costs[myid][id]
		costs[recv_packet[1]][recv_packet[0]] = recv_packet[2];	//costs[id][myid]
		pthread_mutex_unlock(&lock);
		print_costs();
		sleep(5);
	}
}


// run_link_state
void *run_link_state (void *arg)
{
	int taken[N];
	int min, spot;
	int i, j;
	int r;

	while (1)
	{
		r = rand () % 10;
		sleep (r);
	
		for (i = 0; i < N; i++)
		{
			taken[i] = 0;
			pthread_mutex_lock (&lock);
			distances[i] = costs[myid][i];//initialize distances as cost between source myid node and its neighbors
			pthread_mutex_unlock (&lock);
		}
		taken[myid] = 1;
		for (i = 1; i < N; i++)
		{
			min = 1000; //reset min each time as tracing through nodes
			// find closest node
			for(int y = 0; y < N; y++)
			{
				if(distances[y] < min && taken[y] == 0) //as long as the node hasn't already been scanned for min, find min
				{	
					pthread_mutex_lock(&lock);
					min = distances[y]; //set min 
					spot = y; //index of min
					pthread_mutex_unlock(&lock);
				}
			}
			taken[spot] = 1;
			for(int x = 0; x < N; x++)
				printf("%d", taken[x]);
			// recalculate distances
			for (j = 0; j < N; j++)
			{
				if (taken[j] == 0)
				{
					pthread_mutex_lock (&lock);
					distances[j] = MIN (distances[j], (distances[spot] + costs[spot][j]));
					pthread_mutex_unlock (&lock);
				}
			}
		}

		printf ("new distances: ");
		for (i = 0; i < N; i++)
			printf ("%d ", distances[i]);
		printf ("\n");
		sleep(10);
	}
}


// print costs 
void print_costs (void)
{
	// print costs
	int i, j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			printf("%d ", costs[i][j]);
		}
		printf("\n");
	}
}
