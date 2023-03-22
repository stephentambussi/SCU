/*
 *   Stephen Tambussi
 *   COEN379
 *   HW8: problem 3
 *   3/9/23
 *
 *   Write an O(|s| + |t|) algorithm to return the longest prefix of s that matches a suffix of t
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

// Knuth-Morris-Pratt Algorithm
void KMP(string text, string pattern)
{
    int n = text.size();
    int m = pattern.size();
    vector<int> Kp = compute_Kp(pattern);

    int s, i, p;

    s = 0;
    i = 0;
    p = 0; // variable to hold the size of the prefix of pattern
    while (s <= n - m + i)
    {
        // Compare
        while ((i < m) && (pattern[i] == text[s]))
        {
            i++;
            s++;
        }

        p = max(p, i);
        // shift
        if (i == 0) // Immediate mismatch, i.e., no partial match
            s++;

        else
        {
            if (i == m) // complete match
                cout << s - m + 1 << endl;

            // Partial or complete match
            i = Kp[i - 1];
        }
    }

    // print out prefix of pattern
    cout << p-1 << endl;
    cout << "Longest prefix of s: " << pattern.substr(0, p) << endl;

    // print out suffix of text
    cout << s-m << endl;
    cout << "Longest suffix of t: " << text.substr(s-m, p) << endl;
}

int main(int argc, char **argv)
{
    string s = "abcXabcXabcXabcY";
    string t = "abcXabcXabcXabcYabcXabcXabcXabcX";
    // string s = "ABCDABD";
    // string t = "ABCABCDABABCDABCDABDE";
    // string s = "AAAA";
    // string t = "AAABAAAAA";

    KMP(t, s);

    return 0;
}