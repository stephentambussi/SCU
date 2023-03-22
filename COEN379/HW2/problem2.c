/*  
*   Stephen Tambussi
*   COEN379
*   HW2: problem 2
*   1/25/23
*/

/*
*   Randomized quicksort, simulates expected number of swaps 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int T_S = 0; //Total num of swaps across all sim iterations
int S = 0; //Num of swaps per simulation iteration
int T_R = 0; //Total num of random swaps across all sim iterations
int R = 0; //Num of random swaps
int T_N = 0; //Total num of nonpivot swaps across all sim iterations
int N = 0; //Num of nonpivot swaps
int T_P = 0; //Total num of pivot swaps across all sim iterations
int P = 0; //Num of pivot swaps

//Utility function
void printArray(int arr[], int size, int state)
{

    if(state == 0) printf("Unsorted array = [ ");
    else printf("Sorted array   = [ ");
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

//This function returns an array(*) of random numbers within a range
int *generate_array(int lower, int upper, int count)
{
    //allocate memory for array based on count (size of array)
    int *arr = (int *)malloc(count * sizeof(int));
    for(int i = 0; i < count; i++)
    {
        int num = (rand() % (upper - lower + 1)) + lower;
        arr[i] = num;
    }
    printArray(arr, count, 0);
    return arr;
}

int partition(int arr[], int low, int high)
{
    //printf("partition(arr, %d, %d)\n", low, high);
    int pivot = arr[high];
    int i = low;

    for(int j = low; j < high; ++j)
    {
        if(arr[j] < pivot)
        {
            //NON-PIVOT SWAP
            N++;
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    //PIVOT SWAP
    P++;
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;

    return i;
}

void randomQuickSort(int arr[], int low, int high)
{
    //printf("randomQuickSort(arr, %d, %d)\n", low, high);
    if(low >= high) return;

    //RANDOM SWAP
    R++;
    int rand_idx = rand() % (high - low + 1) + low;
    int temp = arr[rand_idx];
    arr[rand_idx] = arr[high];
    arr[high] = temp;

    int k = partition(arr, low, high);
    randomQuickSort(arr, low, k-1);
    randomQuickSort(arr, k+1, high);
}

int main(int argc, char **argv)
{
    srand(time(0));
    if(argc < 5)
    {
        printf("ERROR: incorrect number of cmd line args.\n");
        printf("./a.out <array_lower_bound> <array_upper_bound> <array_size> <sim_runs>\n");
        return -1;
    }

    int low = atoi(argv[1]);
    int up = atoi(argv[2]);
    int size = atoi(argv[3]);
    int sim_runs = atoi(argv[4]);

    int *arr_ptr = generate_array(low, up, size);

    int *arr_copy = (int *)malloc(size * sizeof(int));

    for(int i = 0; i < sim_runs; i++)
    {
        S = 0;
        R = 0;
        N = 0;
        P = 0;
        memcpy(arr_copy, arr_ptr, size * sizeof(int)); //Reinitializes arr_copy with randomly generated array (arr_ptr) so that input array remains fixed
        //printArray(arr_copy, size, 0);
        randomQuickSort(arr_copy, 0, size - 1);
        //printArray(arr_copy, size, 1);
        T_R += R;
        T_N += N;
        T_P += P;
        S = R + N + P;
        //printf("S = %d for iteration %d\n", S, i);
        T_S += S;
    }

    double E_R = T_R / (double) sim_runs; //Calculate expected num or random swaps
    double E_N = T_N / (double) sim_runs; //Calculate expected num of nonpivot swaps
    double E_P = T_P / (double) sim_runs; //Calculate expected num of pivot swaps
    double E_S = T_S / (double) sim_runs; //Calculate expected total num of swaps
    printf("E[N] = %f\n", E_N);
    printf("E[P] = %f\n", E_P);
    printf("E[R] = %f\n", E_R);
    printf("E[S] = %f\n", E_S);

    free(arr_ptr);
    free(arr_copy);
    return 0;
}