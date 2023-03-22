/*
 *   Stephen Tambussi
 *   COEN379
 *   3/14/23
 *
 *   Studying for final
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Print formatting helper function
void print_string(string s, string header)
{
    cout << header << "\t";
    for (int i = 0; i < s.length(); i++)
    {
        cout << s[i] << "  ";
    }
    cout << endl;
}

// Print formatting helper function
void print_vector(vector<int> arr, string header)
{
    cout << header << "\t";
    for (int i = 0; i < arr.size(); i++)
    {
        (arr[i] == -1)
            ? (cout << "*" << "  ")
            : ((arr[i] > 9) ? (cout << arr[i] << " ") : (cout << arr[i] << "  "));
    }
    cout << endl;
}

// Compute the Z values of string s
vector<int> compute_z(string s)
{
    int l = 0;
    int r = 1;
    int n = s.size();
    vector<int> z(n, 0); // z is array of size n, initialized to 0

    for (int k = 1; k < n; k++)
    {
        int x;
        if (r <= k) // case 1: brute force
        {
            int x = 0;
            while ((k + x < n) && (s[x] == s[k + x]))
                x++;

            z[k] = x;
            l = k;
            r = k + z[k];
        }
        else if (k + z[k - l] < r) // case 2: z[k] = z[k-l]
        {
            z[k] = z[k - l];
        }
        else // case 3: z[k] is at least r - k
        {
            int x = r - k;
            while ((k + x < n) && (s[x] == s[k + x]))
                x++;
            z[k] = x;
            l = k;
            r = k + z[k];
        }
    }

    return z;
}

// Compute the N values of string s
vector<int> compute_n(string s)
{
    int n = s.size();
    vector<int> N(n, 0); // N is array of size n, initialized to 0

    string s_p(s); // copy string

    reverse(s_p.begin(), s_p.end()); // reverse the copied string

    N = compute_z(s_p); // Compute z values on reversed string

    reverse(N.begin(), N.end()); // Reverse the z values to get final N values

    return N;
}

// Compute the N values of string s using brute force (for reference)
vector<int> bruteforce_n(string s)
{
    int n = s.size();
    vector<int> N(n, 0); // N is array of size n, initialized to 0
    for (int i = 0; i < n - 1; i++)
    {
        int b = n - 1; // iterator for full string
        int m = i;     // size of suffix substring/iterator for substring
        while (b > -1 && m > -1)
        {
            if (s[b] == s[m])
            {
                N[i]++;
                b--;
                m--;
            }
            else
                break;
        }
    }
    return N;
}

// Compute the K' values of string s
vector<int> compute_Kp(string s)
{
    int n = s.size();
    vector<int> ans(n, 0), z = compute_z(s);

    for (int i = n - 1; i > 0; i--)
    {
        ans[i + z[i] - 1] = z[i];
    }

    return ans;
}

// Compute the L' values of string s
vector<int> compute_Lp(string s)
{
    int n = s.size();

    vector<int> N = compute_n(s);
    vector<int> ans(n, -1);

    for (int k = 0; k < n; k++)
    {
        if (N[k] > 0)
            ans[n - 1 - N[k]] = k;
    }

    return ans;
}

// Compute the l' values of string s
vector<int> compute_lp(string s)
{
    int n = s.size();

    vector<int> N = compute_n(s);
    vector<int> ans(n, 0);

    int last = 0;
    ans[n - 1] = 0;

    for (int i = n - 2; i >= 0; i--)
    {
        int k = n - 1 - i;
        if (N[k - 1] == k)
        {
            ans[i] = k;
            last = k;
        }
        else
            ans[i] = last;
    }

    return ans;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Error: not enough arguments" << endl;
        return -1;
    }

    string str = argv[1];
    // string str = "aaaabbbbaaaabbbbaaaa";
    // string str = "ABRACADABRA";
    // string str = "abaabaaab";

    print_string(str, "String s:");

    print_vector(compute_z(str), "Z-values:");

    // print_vector(bruteforce_n(str), "BF N-values:");

    print_vector(compute_n(str), "N-values:");

    print_vector(compute_Kp(str), "K'-values:");

    print_vector(compute_Lp(str), "L'-values:");

    print_vector(compute_lp(str), "l'-values:");

    return 0;
}