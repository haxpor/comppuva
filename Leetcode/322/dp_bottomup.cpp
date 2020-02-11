/**
 * Problem 322 - https://leetcode.com/problems/coin-change/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input coin value separated by white space
 * TC#1 Input amount to make up from coin changes to such amount
 * TC#1 Expect number of possibility to make such coin change
 * TC#2 ... and so on
 *
 * Time complexity: O(S*N) 
 * Space complexity: O(S) for lookup table + 1 auxiliary minCost to keep track of minimum coins used
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <limits>
#include <algorithm>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        // if there's no coins, we cannot make a change
        if (coins.size() == 0)
            return -1;
        // if amount if zero, we can do nothing
        if (amount == 0)
            return 0;
        // if negative amount, cannot comply
        if (amount < 0)
            return -1;

        // minus 1 to not get it overflowed and wrapped around to negative number
        const int dummyMaxCheck = std::numeric_limits<int>::max()-1;

        std::vector<int> lookup (amount + 1, dummyMaxCheck);    
        lookup[0] = 0;      // base case of no amount, thus no coins used

        const int coinSize = coins.size();
        for (int i=1; i<=amount; ++i)
        {
            for (int j=0; j<coinSize; ++j)
            {
                if (coins[j] <= i)
                {
                    lookup[i] = std::min(lookup[i], lookup[i - coins[j]] + 1);
                }
            }
        }
        return lookup[amount] == dummyMaxCheck ? -1 : lookup[amount];
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases
    infile.ignore();

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile, line);
        std::istringstream lineStream(line);
        std::vector<int> inputs;

        // get list of input numbers
        int num;
        while (lineStream >> num)
        {
            inputs.push_back(num);
        }

        int amount;
        infile >> amount;

        int expect;
        infile >> expect;
        infile.ignore();

        // compute
        int out = sol.coinChange(inputs, amount);
        if (out == expect)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, out, expect);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out, expect);
        }
    }

    infile.close();

    return 0;
}
