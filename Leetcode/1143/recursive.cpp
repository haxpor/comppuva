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
 * Time complexity: O(2^(N+M))
 * Space complexity: O(1) with stack space for recursive call
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
        return lcs(text1, text2, text1.size(), text2.size());
    }
private:
    int lcs(const std::string& text1, const std::string& text2, int t1Size, int t2Size)
    {
        if (t1Size == 0 || t2Size == 0)
            return 0;

        if (text1[t1Size-1] == text2[t2Size-1])
            return 1 + lcs(text1, text2, t1Size-1, t2Size-1);

        return std::max(lcs(text1, text2, t1Size, t2Size-1), lcs(text1, text2, t1Size-1, t2Size));
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
