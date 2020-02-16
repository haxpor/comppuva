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
 * Time complexity: O(N*M) for recursion depth
 * Space complexity: O(N) + 1 auxiliary variable to keep track of total possible combination (included permutation)
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
        std::vector<int> memo (target + 1, -1);
        return combinationSum4_recur(nums, target, memo);
    }
private:
    int combinationSum4_recur(const std::vector<int>& nums, int target, std::vector<int>& memo)
    {
        if (target == 0)
            return 1;   // count all possible cases
        if (target < 0)
            return -1;

        if (memo[target] != -1)
            return memo[target];

        int totalCount = 0;
        for (int i=0; i<nums.size(); ++i) {
            int res = combinationSum4_recur(nums, target - nums[i], memo);
            if (res != -1)
                totalCount += res;
        }
        memo[target] = totalCount;
        return totalCount;
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
