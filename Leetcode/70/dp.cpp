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
 * Space complexity: O(1) + recursive call cost
 * 
 * This solution will get TLE
 */
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdio>

class Solution {
public:
    int climbStairs(int n) {
        if (n == 0)
            return 1;
        else if (n == 1)
            return 1;

        return climbStairs(n-1) + climbStairs(n-2);
    }
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
