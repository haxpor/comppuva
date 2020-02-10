/**
 * Problem 190 - https://leetcode.com/problems/reverse-bits/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Expect number
 * TC#2 ... and so on
 *
 * Time complexity: O(1)
 * Space complexity: O(1) + 1 auxiliary string
 */
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <bitset>
#include <algorithm>

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        // reverse input number
        std::string bitstring = std::bitset<sizeof(uint32_t) * 8>(n).to_string();
        std::reverse(bitstring.begin(), bitstring.end());
        // convert to unsigned integer
        return static_cast<uint32_t>(std::stoul(bitstring, nullptr, 2));
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

    for (int i=0; i<N; ++i)
    {
        std::getline(infile, line);
        // convert into unsigned integer
        uint32_t input = static_cast<uint32_t>(std::stoul(line, nullptr, 2));

        std::getline(infile, line);
        // convert into unsigned integer
        uint32_t expect = static_cast<uint32_t>(std::stoul(line, nullptr, 2));

        // compute
        int out = sol.reverseBits(input);
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
