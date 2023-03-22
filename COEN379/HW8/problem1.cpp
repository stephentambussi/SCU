/*
 *   Stephen Tambussi
 *   COEN379
 *   HW8: problem 1 - exercise 32.2-1 from textbook
 *   3/9/23
 *
 *   This is an implementation of the rabin-karp string matcher
 */
#include <iostream>
#include <string>
#include <array>

using namespace std;

int N = 16;
int M = 2;

void rabin_karp(int t[], int p[], int q, int d)
{
    int n = N;
    int m = M;

    // pre-compute k = d^(m-1)
    int k = 1;
    for (int i = 1; i < m; ++i)
    {
        k = (k * d) % q;
    }

    // convert p and t[0..m-1] to integers
    int T = 0, P = 0;
    for (int i = 0; i < m; ++i)
    {
        P = ((P * d) + p[i]) % q;
        T = ((T * d) + t[i]) % q;
    }

    // compare and shift by one
    for (int s = 0; s <= n - m; ++s)
    {
        if((P - T) % q == 0)
            cout << "Pattern occurs with shift " << s << "\tValue matched: " << t[s] << t[s+1] << endl;
        T = (d * (T - (t[s] * k)) + t[s+m]) % q;
    }
}

int main(int argc, char **argv)
{
    //"31 41 59 26 53 58 97 93" text in ascii
    //char txt[] = "\x1f\x29\x3b\x1a\x35\x3a\x61\x5d";
    int txt[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3};
    //char txt[] = "3141592653589793";
    //"26" //pattern in ascii
    //char pat[] = "\x1a";
    //char pat[] = "26";
    int pat[] = {2, 6};
    int q = 11;
    int d = 256; //Number of ascii characters
    rabin_karp(txt, pat, q, d);
}