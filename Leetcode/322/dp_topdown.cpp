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
 *
 * TLE
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
        std::sort(coins.begin(), coins.end());
        // count is lookup table
        std::vector<int> count (amount, -1);
        return coinChange(coins, amount, count);
    }
private:
    int coinChange(const std::vector<int>& coins, int amount, std::vector<int>& count)
    {
        // amount is 0
        if (amount == 0)
            return 0;
        // negative amount, cannot comply
        if (amount < 0)
            return -1;

        // check for cached result
        if (count[amount-1] != -1)
            return count[amount-1];

        int minCost = std::numeric_limits<int>::max();
        // iterate reversely to use big value coin first
        for (auto it=coins.rbegin(); it!=coins.rend(); ++it)
        {
            int coinVal = *it;
            int res = coinChange(coins, amount-coinVal, count);
            if (res != -1 && res < minCost)
            {
                minCost = res + 1;
            }
        }
        count[amount - 1] = minCost == std::numeric_limits<int>::max() ? -1 : minCost;
        return count[amount - 1];
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
