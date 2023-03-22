/*  
*   Stephen Tambussi
*   COEN379
*   HW1: problem 1
*   1/19/23
*/

/*
*   Use a Monte Carlo simulation with 10 million iterations to esimate the area enclosed by the curve whose equation is (x^2 + y^2 − 4)^3 − 108y^2 = 0.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

size_t MAX = 2147483647;
size_t iter = 10000000;

double area(int n)
{
    srand(time(0));
    double in = 0;
    for(int i = 1; i <= n; ++i)
    {
        double max = (double) MAX - 1;
        double x = rand() / max;
        x = x * (2 * sqrt(2));
        double y = rand() / max;
        y = y * 4;
        double t = (x*x + y*y - 4.0);
        if((t*t*t) - (108.0*(y*y)) <= 0)
            ++in;
    }
    return 4.0 * (in/n * (4 * 2 * sqrt(2)));
}

int main()
{
    printf("Area = %f\n", area(iter));
}