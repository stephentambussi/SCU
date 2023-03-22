/*  
*   Stephen Tambussi
*   COEN379
*   HW3: problem 2
*   2/2/23
*/

/*
*   Finds the first 20 carmichael numbers 
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int powermod(unsigned long x, unsigned long y, unsigned long m) //return x^y (mod m)
{
    if(y == 0)
        return 1;
    unsigned long temp = powermod(x, y/2, m);

    if(y % 2 == 0)
        return (temp * temp) % m;
    else
        return (((temp * temp) % m) * x) % m;
}

//Greatest common divisor
int gcd(unsigned long a, unsigned long b)
{
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

//Performs Fermat test for primality
bool fermat(unsigned long N, unsigned long a)
{
    if(gcd(a, N) != 1 || powermod(a, N-1, N) != 1)
        return false;
    return true;
}

//Performs Miller-Rabin test for primality
bool miller_rabin(unsigned long N, unsigned long a)
{
    if(N == 2)
        return true;
    
    unsigned long d, s;
    for(d = N - 1, s = 0; d % 2 == 0; d /= 2)
        ++s;
    
    if(gcd(a, N) != 1)
        return false;
    
    unsigned long x = powermod(a, d, N);
    if(x == 1 || x == N - 1)
        return true;
    for(int r = 1; r < s; ++r)
    {
        x = (x * x) % N;
        if(x == N - 1)
            return true;
    }
    return false;
}

//Finds carmichael numbers
bool carmichael(unsigned long n)
{
    bool fermat_prime = true;
    bool mr_prime = true;
    for(int i = 1; i <= 100; ++i)
    {
        unsigned long a1 = rand() % (n - 1) + 1;
        unsigned long a2 = rand() % (n - 1) + 1;
        if(gcd(a1, n) != 1)
            continue;
        fermat_prime = fermat_prime && fermat(n, a1);
        mr_prime = mr_prime && miller_rabin(n, a2);
    }
    return (fermat_prime && !mr_prime);
}

int main(int argc, char **argv)
{
    srand(time(0));
    int cnt = 0;
    unsigned long num1 = 2;
    while(cnt < 20)
    {
        if(carmichael(num1))
        {
            cnt++;
            printf("%ld\n", num1);
        }
        num1++;
    }
    return 0;
}