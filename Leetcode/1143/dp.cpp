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
 * Time complexity: <to-be-filled>
 * Space complexity: <to-be-filled>
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
            return 0;

        std::string& t1 = text1.size() >= text2.size() ? text1 : text2;
        std::string& t2 = text1.size() < text2.size() ? text2 : text1;

        const int ts1 = t1.size();
        const int ts2 = t2.size();

        int dp[2][ts2];
        std::memset(dp, 0, 2*ts2*sizeof(int));
        
        for (int i=0; i<ts1; ++i)
        {
            for (int j=0; j<ts2; ++j)
            {
                if (text1[i] == text2[j])
                {
                    
                }
            }
        }       

        return maxGlobal;
    }
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
