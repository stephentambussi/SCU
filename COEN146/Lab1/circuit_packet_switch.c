/* Stephen Tambussi
 * 1/7/21
 * Lab 1 - Circuit and Packet Switching
 * Description: This program performs quantitative comparisons between circuit and packet switching 
 */
#include <stdio.h> //printf, stderr
#include <math.h>
#include <sys/types.h> //pid_t
#include <unistd.h> //fork
#include <stdlib.h> //atoi
#include <errno.h> //errno
unsigned long factorial(unsigned long n)
{
	if(n == 0) return 1;
	return n * factorial(n-1);
}
int main(int argc, char *argv[]) 
{
	int linkBandwidth, userBandwidth, nCSusers, nPSusers;
	double tPSuser, pPSusersBusy, pPSusersNotBusy;
	linkBandwidth = 200; //Mbps
	userBandwidth = 20; //Mbps
	tPSuser = 0.10;
	nPSusers = 19;
	//Circuit Switching
	printf("Circuit Switching scenario\n");
	//Number of supported users in a circuit switched network
	nCSusers = linkBandwidth / userBandwidth;
	printf("Supported users in a circuit switched network with %d link bandwidth and %d user bandwidth\n", linkBandwidth, userBandwidth);
	printf("%d\n", nCSusers);
	//Packet Switching
	printf("Packet Switching scenario\n");
	//Probability that a specific user is busy transmitting
	pPSusersBusy = tPSuser;
	printf("Probability that a specific user is busy transmitting: %f\n", pPSusersBusy);
	//Probability that a other specific user is not busy
	pPSusersNotBusy = 1 - pPSusersBusy;
	printf("Probability that a other specific user is not busy: %f\n", pPSusersNotBusy);
	//Probability that all of the other specific users are not busy
	double result = pow((1 - pPSusersBusy), (nPSusers - 1));
	printf("Probability that all of the other specific users are not busy: %f\n", result);
	//Probability that one specific user is transmitting and the rest are not
	result = pPSusersBusy * pow(pPSusersNotBusy, (nPSusers - 1));
	printf("Probability that one specific user is transmitting and the rest are not: %f\n", result);
	//Probability that exactly one of the nPSusers users is busy
	result = nPSusers * ( pPSusersBusy * pow(pPSusersNotBusy, (nPSusers - 1)));
	printf("Probability that exactly one of the users is busy: %f\n", result);
	//Probability that 10 specific users are transmitting and the others are idle
	result = pow(pPSusersBusy, 10) * pow(pPSusersNotBusy, (nPSusers - 10));
	printf("Probability that 10 specific users are transmitting and the others are idle: %g\n", result);
	//Probability that any 10 users are transmitting and the others are idle
	int t = factorial(nPSusers) / (factorial(10) * factorial(nPSusers - 10));
	result = t * pow(pPSusersBusy, 10) * pow(pPSusersNotBusy, (nPSusers - 10));
	printf("Probability that any 10 users are transmitting and the other are idle: %g\n", result);
	//Probability that more than 10 users are transmitting and the others are idle
	int i;
	double sum = 0;
	for(i = 11; i < nPSusers; i++)
	{
		int bi = factorial(nPSusers) / (factorial(i) * factorial(nPSusers - i));
		sum += bi * pow(pPSusersBusy, i) * pow(pPSusersNotBusy, (nPSusers - i));
	}
	printf("Probability that more than 10 users are transmitting and the others are idle: %g\n", sum);
	return 0;
}
