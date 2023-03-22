/*  
*   Stephen Tambussi
*   COEN379
*   HW1: problem 2
*   1/19/23
*/

//Just to test to see if simulation agrees with formula

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

void simulate(int n, int k)
{
    srand(time(0));

    double weighted_avg = 0.0;
    int sim_runs = 1000000;
    int j = 0;

    while(j < sim_runs)
    {
        int unique = 0;
        vector<int> exists;
        for(int i = 0; i < k; i++)
        {
            int rand_num = rand() % n;
            if(count(exists.begin(), exists.end(), rand_num) == 0)
            {
                exists.push_back(rand_num);
                unique++;
            }
        }
        weighted_avg += double(unique);
        j++;
    }

    cout.precision(4);

    weighted_avg = weighted_avg / sim_runs;

    double temp = (n - 1) / double(n);
    double expected_val = n * (1 - pow(temp, k));
    cout << "Simulated value: " << fixed << weighted_avg << endl;
    cout << "Expected value: " << fixed << expected_val << endl;
    return;
}

int main()
{
    int n1, k1;
    cin >> n1 >> k1;
    simulate(n1, k1);
    return 0;
}