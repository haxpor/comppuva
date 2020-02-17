/**
 * Problem 198 - House Robber - https://leetcode.com/problems/house-robber/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers of money in each house separated by white space
 * TC#1 Expect maximum amount to get
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

class Solution {
public:
    int rob(std::vector<int>& nums) {
        const int size = nums.size();
        if (size == 0)
            return 0;
        else if (size == 1)
            return nums[0];
        else if (size == 2)
            return nums[0] > nums[1] ? nums[0] : nums[1];
        else if (size == 3)
            return nums[0]+nums[2] > nums[1] ? nums[0]+nums[2] : nums[1];

        if (size % 2 == 1) {
            // start at odd
            int oddSum = 0;
            for (int i=0; i<size; i+=2)
                oddSum += nums[i];

            // start at even
            int evenSum = 0;
            int i;
            for (i=1; i<size-2; i+=2)
                evenSum += nums[i];
            if (nums[i+1] > nums[i+2])
                evenSum += nums[i+1];
            else
                evenSum += nums[i+2];

            return oddSum > evenSum ? oddSum : evenSum;
        }
        else {
            // start at odd
            int oddSum = 0;
            int i;
            for (i=0; i<size-2; i+=2)
                oddSum += nums[i];
            --i;
            if (nums[i+1] > nums[i+2])
                oddSum += nums[i+1];
            else
                oddSum += nums[i+2];

            // start at even
            int evenSum = 0;
            for (int i=1; i<size; i+=2)
                evenSum += nums[i];

            return oddSum > evenSum ? oddSum : evenSum;
        }
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
        std::istringstream lineStream(line);
        std::vector<int> inputs;

        // get list of input numbers
        int num;
        while (lineStream >> num)
        {
            inputs.push_back(num);
        }

        int expect;
        infile >> expect;
	infile.ignore();

        // compute
        int out = sol.rob(inputs);
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
