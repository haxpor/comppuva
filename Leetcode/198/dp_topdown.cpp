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
        std::vector<int> memo (nums.size() + 1, -1);
        return rob_recur(nums, 0, memo);
    }
private:
    int rob_recur(const std::vector<int>& nums, int startIdx, std::vector<int>& memo) {
        if (nums.size() == 0)
            return 0;
        if (memo[startIdx] != -1)
            return memo[startIdx];
        if (startIdx == nums.size()-1)
            return nums[startIdx];
        if (startIdx + 1 == nums.size()-1)      // if there is 2 elements left to check, then choose what's greater
            return std::max(nums[startIdx], nums[startIdx+1]);

        int sum1 = nums[startIdx] + rob_recur(nums, startIdx+2, memo);
        int sum2 = rob_recur(nums, startIdx+1, memo);
        memo[startIdx] = std::max(sum1, sum2);
        return memo[startIdx];
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
