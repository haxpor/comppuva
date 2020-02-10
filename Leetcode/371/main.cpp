/**
 * Problem 371 - https://leetcode.com/problems/sum-of-two-integers/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Two numbers separated by white space for operand A and B 
 * TC#1 Expect summation of A and B
 * TC#2 ... and so on
 */
#include <vector>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

class Solution {
public:
    int getSum(int a, int b) {
        if (a == 0)
            return b;
        if (b == 0)
            return a;

        while (b != 0)
        {
            int carry = ((a & b) & 0xFFFFFFFF) << 1;    // need mask to prevent overflow for negative number
            a = a ^ b;
            b = carry;
        }

        return a;
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
        int a, b;
        infile >> a >> b;
        std::istringstream lineStream(line);

        int expect;
        infile >> expect;

        // compute
        int out = sol.getSum(a, b);
        if (out == expect)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, out, expect);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out, expect);
            std::exit(1);
        }
    }

    infile.close();

    return 0;
}
