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
#include <cstring>

class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 && n == 1)
            return 1;

        // max value of m, or n is at most 100
        std::vector<std::vector<int>> dp (n, std::vector<int>(m));
        for (int i=0; i<n; ++i)
            std::memset(&dp[i][0], -1, sizeof(int) * dp[i].size());
        dp[0][0] = 0;

        // base cases
        for (int col=1; col<m; ++col)
            dp[0][col] = 1;
        for (int row=1; row<n; ++row)
            dp[row][0] = 1;

        return solve(m-1, n-1, dp);
    }
private:
    // solve for target m,n of grid
    // m and n are index-based
    int solve(int m, int n, std::vector<std::vector<int>>& dp) {
        if (dp[n][m] != -1)
            return dp[n][m];
        
        // if able to find nearby positions, then return compute the answer for this position in the grid
        if (dp[n-1][m] != -1 && dp[n][m-1] != -1) {
            dp[n][m] = dp[n-1][m] + dp[n][m-1];
            return dp[n][m];
        }
        else {
            return solve(m, n-1, dp) + solve(m-1, n, dp);
        }
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
