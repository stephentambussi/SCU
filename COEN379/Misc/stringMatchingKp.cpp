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
            ? (cout << "*"
                    << "  ")
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

// String matching using K' values
void Kp_sm(string text, string pat)
{
    cout << "Linear-time String Matching Algorithm using K'-values" << endl;
    print_string(text, "Text:\t");
    print_string(pat, "Pattern:");

    int n = text.size();
    int m = pat.size();

    //Create and initialize index vector for text
    vector<int> indices(n, 0);
    for(int x = 0; x < n; x++)
        indices[x] = x;

    string w = pat + "#" + text;
    print_string(w, "Pattern+Text:");

    vector<int> kp = compute_Kp(w);
    // print_vector(compute_z(w), "Z-values:");
    print_vector(kp, "K'-values:");
    
    for(int i = m+1; i < n + m + 1; i++)
    {
        if(kp[i] == m)
        {
            cout << endl;
            cout << "MATCHED: '" << pat << "'" << endl;
            print_vector(indices, "Indices:");
            print_string(text, "Text:\t");
            
            //To visualize the matched string
            string ptr(n, ' ');
            for(int x = i-(m*2); x < i-m; x++)
            {
                ptr[x] = '^';
            }

            print_string(ptr, "\t");

            // Debugging
            // cout << i-(m*2) << endl;
            // cout << i-m-1 << endl;

            return;
        }
    }

    cout << endl;
    cout << "NO MATCH FOUND" << endl;
    return;
}

/* K'-value string matching vs Z'-value
 * 
 * When Z[i] == m (length of pattern to match) Z[i] occurs at the
 * first index of the pattern found in the text. For K'-values,
 * when K'[i] == m, K'[i] occurs at the last index of the pattern 
 * found in the text. Therefore, string matching using K'-values 
 * is essentially the same as when using Z-values.
 * 
 *                 Example
 * Text:           A  B  R  A  C  A  D  A  B  R  A
 * Pattern:        A  B  R  A
 *                                v-- first index of 'ABRA'
 * Pattern+Text:   A  B  R  A  #  A  B  R  A  C  A  D  A  B  R  A
 * Z-values:       0  0  0  1  0  4  0  0  1  0  1  0  4  0  0  1
 * K'-values:      0  0  0  1  0  0  0  0  4  0  1  0  0  0  0  4
 *                                         ^-- last index of 'ABRA'
 */

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "Error: not enough arguments" << endl;
        return -1;
    }

    string text = argv[1];
    string pat = argv[2];

    Kp_sm(text, pat);

    return 0;
}