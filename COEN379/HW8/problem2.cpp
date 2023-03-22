/*
 *   Stephen Tambussi
 *   COEN379
 *   HW8: problem 2 - variation of the z algorithm
 *   3/9/23
 *
 *   Write an O(|s|) algorithm based on the Z algorithm to compute the N-values of a string s, defined as follows:
 *      N(|s| - 1) = 0;
 *      N(i) is the length of the longest common suffix of s and s[0..i] for 0 <= i < |s| - 1
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> compute_z(string s)
{
    int l = 0;
    int r = 1;
    int n = s.size();
    vector<int> z(n, 0); // z is array of size n, initialized to 0

    for (int k = 1; k < n; k++)
    {
        int x;
        if (r <= k)                 // case 1: brute force
        {
            int x = 0;
            while ((k + x < n) && (s[x] == s[k + x]))
                x++;

            z[k] = x;
            l = k;
            r = k + z[k];
        }
        else if (k + z[k-l] < r)    // case 2: z[k] = z[k-l]
        {
            z[k] = z[k-l];
        }
        else                        // case 3: z[k] is at least r - k
        {
            int x = r - k;
            while((k + x < n) && (s[x] == s[k + x]))
                x++;
            z[k] = x;
            l = k;
            r = k + z[k];
        }
    }

    return z;
}

//Compute the n values of string s
vector<int> compute_n(string s)
{
    int n = s.size();
    vector<int> N(n, 0); // N is array of size n, initialized to 0
    
    string s_p(s); //copy string

    reverse(s_p.begin(), s_p.end()); //reverse the copied string

    N = compute_z(s_p); //Compute z values on reversed string

    reverse(N.begin(), N.end()); //Reverse the z values to get final N values

    return N;
}

vector<int> bruteforce_n(string s)
{
    int n = s.size();
    vector<int> N(n, 0); // N is array of size n, initialized to 0
    for(int i = 0; i < n - 1; i++)
    {
        int b = n - 1; //iterator for full string
        int m = i; //size of suffix substring/iterator for substring
        while(b > -1 && m > -1)
        {
            if(s[b] == s[m])
            {
                N[i]++;
                b--;
                m--;
            }
            else break;
        }
    }
    return N;
}

int main(int argc, char **argv)
{
    string str = "aaaabbbbaaaabbbbaaaa";
    //string str = "ABRACADABRA";
    //string str = "abaabaaab";
    vector<int> ans = compute_z(str);
    cout << "Z-values for ref   : ";
    for(int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    vector<int> ans1 = bruteforce_n(str);
    cout << "Bruteforce N-values: ";
    for(int i = 0; i < ans1.size(); i++)
    {
        cout << ans1[i] << " ";
    }
    cout << endl;

    vector<int> ans2 = compute_n(str);
    cout << "N-values w/ Z-algo : ";
    for(int i = 0; i < ans2.size(); i++)
    {
        cout << ans2[i] << " ";
    }
    cout << endl;

    return 0;
}