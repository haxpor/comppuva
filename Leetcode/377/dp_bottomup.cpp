/**
 * Problem 377 - Combination Sum IV - https://leetcode.com/problems/combination-sum-iv/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Target sum
 * TC#1 Expect combination (not unqiue permutation)
 * TC#2 ...
 *
 * Time complexity: O(N*M)
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
    int combinationSum4(std::vector<int>& nums, int target) {
        if (target == 0)
            return 0;
        if (nums.size() == 0)
            return 0;

        std::vector<uint64_t> dp (target + 1, 0);
        dp[0] = 1;

        for (int i=1; i<=target; ++i) {
            for (int j=0; j<nums.size(); ++j) {
                if (nums[j] <= i) {
                    dp[i] += dp[static_cast<uint64_t>(i) - nums[j]];   // count only if coin used
                }
            }
        }

        return dp[target];
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

        // get target sum
        int targetSum;
        infile >> targetSum;

        // get expect combination
        int expect;
        infile >> expect;
        infile.ignore();

        // compute
        int out = sol.combinationSum4(inputs, targetSum);
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
