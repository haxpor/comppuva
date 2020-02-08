/**
 * Problem 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * Testcase#1 Input numbers separated by white space
 * Testcase#1 Target number
 * Testcase#1 Expect number
 * Testcase#2 ... and so on
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile.ignore(), line); // need to ignore left-out byte (newline) from previously extraction operator
                                             // otherwise, we will read newline instead
        std::istringstream lineStream(line);
        std::vector<int> inputs;

        int num;

        // get list of input numbers
        while (lineStream >> num)
        {
            inputs.push_back(num);
        }

        // get target
        infile >> num;

        int expect;
        infile >> expect;

        // compute
        int search = sol.search(inputs, num);
        if (search == expect)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, search, expect);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, search, expect);
            std::exit(1);
        }
    }

    infile.close();

    return 0;
}
