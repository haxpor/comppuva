/**
 * Problem 128 - Longest Consecutive Sequence
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of number
 * TC#1 Expect number
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(1) (2 auxiliary)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "ArrayInputParser.h"

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return 1;

        std::sort(nums.begin(), nums.end());

        int streak = 1;
        int localStreak = 1;
        for (int i=1; i<nums.size(); ++i) {
            if (nums[i] != nums[i-1]) {
                if (nums[i] == nums[i-1]+1) {
                    ++localStreak;
                }
                else {
                    streak = std::max(streak, localStreak);
                    localStreak = 1;
                }
            }
        }

        return std::max(streak, localStreak);
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
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);

        // get expect number
        int expect;
        infile >> expect;

        // compute
        int out = sol.longestConsecutive(nums);
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
