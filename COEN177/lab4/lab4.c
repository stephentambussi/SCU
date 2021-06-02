/* Name: Stephen Tambussi
 * Date: 4/22/2021
 * Title: Lab4 - Developing multi-threaded applications
 * Description: This program does matrix multiplication through multithreading
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//values of N,M, and L 
//test
#define N 1024  
#define M 1024
#define L 1024

//max value of random numbers that matrix can be initialized with
#define R 11

pthread_t threads[N];

//A, B, C matrices
double matrixA[N][M], matrixB[M][L], matrixC[N][L];

//function prototypes
void initializeMatrix(int r, int c, double matrix[r][c]);
void *multiplyRow(void* arg);
void printMatrix(int r, int c, double matrix[r][c]);

int main()
{
	int i;
	initializeMatrix(N, M, matrixA);  //initilaize matrixA with random values
	sleep(1); //wait for the random number seed to change so matrices are different
	initializeMatrix(M, L, matrixB); //initialize matrixB with random values
	//create N threads, each multiplying row A by all columns fo B to produce row of C
	for(i = 0; i < N; i++)
	{
		pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t)i); //cast i to size_t then to void pointer type -- passes value of i instead of address
	}
	//Main thread waits for child threads to complete
	for(i=0;i<N;i++)
	{
		pthread_join(threads[i],NULL);
	}

	//Print Matrix A, B, and C
	printf("Matrix A: \n");
	printMatrix(N, M, matrixA);
	printf("Matrix B: \n");
	printMatrix(M, L, matrixB);
	printf("Matrix C: \n");
	printMatrix(N, L, matrixC);
	return 0;
}

//Initialize matrixA and matrixB with random values
void initializeMatrix(int r, int c, double matrix[r][c])
{
	srand(time(NULL));
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
			matrix[i][j] = rand() % R;
}

//thread function: multiply row of A by columns of B --> row of C
void* multiplyRow(void *arg)
{

	int i = (int)(size_t *)arg; //casts arg to size_t pointer then to int type -- gets value of i from main()
	for(int j = 0; j < L; j++)
	{
		double temp = 0;
		for(int k = 0; k < M; k++)
			temp += matrixA[i][k] * matrixB[k][j];
		matrixC[i][j] = temp;
	}	
    	return 0;
}

//Print matrices
void printMatrix(int r, int c, double matrix[r][c])
{
	int i, j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
			printf("%lf ",matrix[i][j]);
		printf("\n");
	}
}
