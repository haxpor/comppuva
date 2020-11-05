/**
 * Problem 3 - Longest Substring Without Repeating Characters
 *
 * Format of testcase.txt is as follows
 *
 * ---- start of testcases.txt file format ----
 * Number of testcases
 * TC#1 Input string (NUL for empty string)
 * TC#1 Expect output
 * TC#2 ... and so on
 * ---- end of testcases.txt file format ----
 *
 * Naive solution
 * TLE
 *
 * Time complexity: O(N^3)
 * Space complexity: O(k) wheres k is size of set
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string_view>
#include <set>
#include <algorithm>
#include "ArrayInputParser.h"

class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        const int length = s.length();
        int longestSubstring = 0;

        std::string_view sv = std::string_view(s);

        for (int i=0; i<length; ++i)
        {
            for (int j=i+1; j<=length; ++j)
            {
               if (isAllUnique(sv, i, j))
                   longestSubstring = std::max(longestSubstring, j - i);
            }
        }

        return longestSubstring;
    }

private:
    bool isAllUnique(std::string_view sv, int start, int end)
    {
        std::set<char> uniqueHolder;
        for (int i=start; i<end; ++i)
        {
            char c = sv.at(i);
            if (uniqueHolder.find(c) == uniqueHolder.end())
                uniqueHolder.insert(c);
            else
                return false;
        }

        return true;
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
    ArrayInputParser aparser;

    for (int i=0; i<N; ++i)
    {
        std::string inputStr;
        infile >> inputStr;

        if (inputStr == "NUL")
            inputStr = "";

        //std::getline(infile, line);

        int expect;
        infile >> expect;

        std::cout << "inputStr: " << inputStr << std::endl;
        std::cout << "expect: " << expect << std::endl;

        // compute
        int out = sol.lengthOfLongestSubstring(inputStr);
        if (out == expect)
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, out, expect);
        else
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out, expect);
    }

    infile.close();

    return 0;
}
