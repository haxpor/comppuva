/**
 * Problem 338 - https://leetcode.com/problems/counting-bits/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Input number
 * TC#1 Expect output numbers in array separated by white space
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(N)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    std::vector<int> countBits(int num) {
        std::vector<int> lookup(num + 1, 0);

        // f(n) = f(n >> 1) + (n mod 2)
        lookup[0] = 0;

        for (int i=1; i<=num; ++i)
        {
            lookup[i] = lookup[i >> 1] + (i % 2);
        }        
        return lookup;
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
        // read the input number
        int num;
        infile >> num;
        infile.ignore();

        // read the expected output of numbers
        int num2;
        std::getline(infile, line);
        std::istringstream lineStream(line);
        std::vector<int> expectNumbers;
        while (lineStream >> num2)
        {
            expectNumbers.push_back(num2);
        }

        // compute
        std::vector<int> outs = sol.countBits(num);
        bool priorCheckGood = true;
        if (outs.size() != expectNumbers.size())
        {
            std::printf("[Failed #%d] Size of output mismatch. Output: %ld, Expect: %ld\n", i, outs.size(), expectNumbers.size());
            priorCheckGood = false;
        }

        if (priorCheckGood)
        {
            auto mismatch = std::mismatch(outs.begin(), outs.end(), expectNumbers.begin());
            if (mismatch.first == outs.end() && mismatch.second == expectNumbers.end())
            {
                // match
                std::printf("[Success #%d]\n", i);
            }
            else
            {
                std::printf("[Failed #%d] Mismatch found in output\n", i);
                while (mismatch.first != outs.end() && mismatch.second != expectNumbers.end())
                {
                    std::printf("  Output: %d, Expect: %d\n", *mismatch.first, *mismatch.second);

                    // iterate for all mismatch
                    if (mismatch.first != outs.end())
                        ++mismatch.first;
                    if (mismatch.second != expectNumbers.end())
                        ++mismatch.second;
                }
            }
        }
    }

    infile.close();

    return 0;
}
