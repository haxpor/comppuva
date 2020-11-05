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
 * Optimized version (sliding window)
 *
 * Time complexity: O(n)
 * Space complexity: O(k) wheres k is the size of the set
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
        std::set<char> uniqueHolder;
        int ans = 0;
        int i = 0;
        int j = 0;
        while (i < length && j < length)
        {
            if (uniqueHolder.find(s.at(j)) == uniqueHolder.end())
            {
                uniqueHolder.insert(s.at(j++));
                ans = std::max(ans, j - i);
            }
            else
            {
                uniqueHolder.erase(s.at(i++));
            }
        }
        return ans;
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
