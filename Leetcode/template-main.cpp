/**
 * Problem 
 *
 * Format of testcase.txt is as follows
 *
 * ---- start of testcases.txt file format ----
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Expect number
 * TC#2 ... and so on
 * ---- end of testcases.txt file format ----
 *
 * Time complexity: <to-be-filled>
 * Space complexity: <to-be-filled>
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "ArrayInputParser.h"

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
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);

        int expect;
        infile >> expect;

        // compute
        int out = sol.search(inputs, num);
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
