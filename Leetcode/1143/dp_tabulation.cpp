/**
 * Problem 1143 - https://leetcode.com/problems/longest-common-subsequence/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Text1 input follows by white space then Text2 input
 * TC#1 Expect longest common subsequence
 * TC#2 ... and so on
 *
 * Time complexity: O(N*M)
 * Space complexity: O(N*M)
 */
#include <vector>
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>

class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        if (text1.size() == 0 || text2.size() == 0)
        {
            return 0;
        }

	    std::memset(dp, 0, 1001 * 1001 * sizeof(int));

        const int t1size = text1.size();
        const int t2size = text2.size();

        for (int i=1; i<t1size+1; ++i)
        {
            for (int j=1; j<t2size+1; ++j)
            {
                if (text1[i-1] == text2[j-1])
                   dp[i][j] = 1 + dp[i-1][j-1];
                else
                   dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]); 
            }
        }

        return dp[t1size][t2size];
    }
private:
    int dp[1001][1001];		// maximum length of both string is 1000
};

int main()
{
    std::ifstream infile("testcases.txt");

    int N;
    infile >> N;    // read number of testcases

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::string text1;
        std::string text2;

        // read text1/2 input
        infile >> text1 >> text2;

        int expect;
        infile >> expect;

        // compute
        int out = sol.longestCommonSubsequence(text1, text2);
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
