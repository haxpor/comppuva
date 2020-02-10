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
        : lookup(std::vector<int>(100, -1))       // maximum number of N input from Leetcode is by guess and estimated here
        , maxComputed(0)
    {
        lookup[0] = 1;
        lookup[1] = 1;
        maxComputed = 1;
    }

    int climbStairs(int n) {
        if (n < 2)
            return lookup[n];
        
        if (lookup[n] != -1)
            return lookup[n];

        // compute further, not re-compute from scratch
        for (int i=maxComputed+1; i<=n; ++i)
        {
            lookup[i] = lookup[i-1] + lookup[i-2];
        }
        maxComputed = n;
        return lookup[n];
    }
private:
    std::vector<int> lookup;
    int maxComputed;
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
