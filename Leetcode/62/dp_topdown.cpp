/**
 * Problem 62 - Unique Paths - https://leetcode.com/problems/unique-paths/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input M
 * TC#1 Input N
 * TC#1 Expect output
 * TC#2 ... and so on
 *
 * Time complexity: O(M*N)
 * Space complexity: O(M*N)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>

class Solution {
public:
    int uniquePaths(int m, int n) {
        
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
        // get m, and n
        int m,n;
        infile >> m >> n;

        // get expect output
        int expect;
        infile >> expect;

        // compute
        int out = sol.uniquePaths(m, n);
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
