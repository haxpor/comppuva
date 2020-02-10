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
 * Time complexity: O(N^2)
 * Space complexity: O(N) + 2 auxiliary variables
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
        std::vector<int> results;

        for (int i=0; i<=num; ++i)
        {
            int count = 0;
            int currNum = i;
            while (currNum != 0)
            {
                if (( currNum & 0x1) == 1)
                //if (( (currNum & 0xFFFFFFFF) & 0x1) == 1)     // not necessary for masking as it's defined by language standard
                    ++count;
                currNum = currNum >> 1;
            }
            results.push_back(count);
        }        
        return results;
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
