/* Stephen Tambussi
 * 1/21/21
 * Lab 3 - Network commands and HTTP
 * Description: This program performs the calculations for step 3 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int RTT0 = 3; //ms
	int RTT1 = 20;
	int RTT2 = 26;
	int RTTHTTP = 47;
	int n = atoi(argv[1]); //for part c
	
	//a
	int a = RTT0 + RTT1 + RTT2 + (2*RTTHTTP);
	printf("Time to receive 1 object = %d ms\n", a);

	//b
	int b = RTT0 + RTT1 + RTT2 + (14*RTTHTTP);
	printf("Time to receive base object and 6 additional objects = %d ms\n", b);
	
	//c
	double packets = (n >= 6) ? 1 : 6.0/n;
	int parallel = ceil(packets);

	//non-persistent
	int np_c = RTT0 + RTT1 + RTT2 + (2*RTTHTTP) + (2*parallel*RTTHTTP);
	printf("Time to receive objects with n parallel connections & non-persistent HTTP = %d ms\n", np_c);

	//persistent
	int p_c = RTT0 + RTT1 + RTT2 + (2*RTTHTTP) + (parallel * RTTHTTP);
	printf("Time to receive objects with n parallel connections & persistent HTTP = %d ms\n", p_c);
	return 0;
}
