/**
 * Problem 70 - https://leetcode.com/problems/climbing-stairs/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input number of N steps of the problem
 * TC#1 Expect number of distinct way we can climb
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(N) + recursive call cost
 * 
 */
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdio>

class Solution {
public:
    Solution()
        : memo(std::vector<int>(100, -1))
    {
        memo[0] = 1;
        memo[1] = 1;
    }

    int climbStairs(int n) {
        if (memo[n] != -1)
            return memo[n];

        if (n == 0)
            return 1;
        else if (n == 1)
            return 1;

        memo[n] = climbStairs(n-1) + climbStairs(n-2);
        return memo[n];
    }
private:
    std::vector<int> memo;
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        // get steps
        int steps;
        infile >> steps;

        // get expect distinct number of ways
        int expectWays;
        infile >> expectWays;

        // compute
        int out = sol.climbStairs(steps);
        if (out == expectWays)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, out, expectWays);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out, expectWays);
        }
    }

    infile.close();

    return 0;
}
