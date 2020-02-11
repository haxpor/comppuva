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
 * Time complexity: O(S^N)
 * Space complexity: O(N)
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

// this one borrowed and modified from https://leetcode.com/problems/coin-change/solution/
class Solution {
public:
    // ensure coins is sorted
    int coinChange(std::vector<int>& coins, int amount)
    {
        std::sort(coins.begin(), coins.end());
        return coinChange(coins, coins.size()-1, amount);
    }
private:
    int coinChange(const std::vector<int>& coins, int idxCoin, int amount)
    {
        if (amount == 0)
            return 0;

        if (idxCoin < coins.size() && amount > 0)
        {
            int maxNumCoins = amount / coins[idxCoin];
            int minCost = std::numeric_limits<int>::max();
            for (int n=0; n<=maxNumCoins; ++n)
            {
                if (amount >= n * coins[idxCoin])
                {
                    int res = coinChange(coins, idxCoin - 1, amount - n*coins[idxCoin]);
                    if (res != -1)
                        minCost = std::min(minCost, res + n);
                }
            }
            steps++;
            return (minCost == std::numeric_limits<int>::max() ? -1 : minCost);
        }
        return -1;
    }
private:
    int steps;
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
