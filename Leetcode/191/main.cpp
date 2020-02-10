/**
 * Problem 191 - https://leetcode.com/problems/number-of-1-bits/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 String of bit (0/1) representing unsigned integer
 * TC#1 Target number of 1s bit count
 * TC#2 ... and so on
 */
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdint>

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while (n != 0)
        {
            if ((n & 0x1) == 1)
                ++count;
            n = n >>1;
        }
        return count;
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
        // get the bitstring
        std::string bitstring;
        infile >> bitstring;

        // convert from bitstring to unsigned integer
        // note: input bitstring is expected to be in unsigned integer, then we need to use std::stol
        // to be able to hold the number without overflow problem
        uint32_t inputNum = static_cast<uint32_t>(std::stol(bitstring, nullptr, 2));

        int expect;
        infile >> expect;

        // compute
        int out = sol.hammingWeight(inputNum);
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
