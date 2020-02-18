/**
 * Problem 213 - House Robber - https://leetcode.com/problems/house-robber-ii/
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
#include <cstring>

class Solution {
public:
    int rob(std::vector<int>& nums) { 
        const int size = nums.size();
        if (size == 0)
            return 0;
        if (size == 1)
            return nums[0];
        if (size == 2)
            return nums[0]>nums[1] ? nums[0] : nums[1];
        if (size == 3)
            return std::max(nums[0], std::max(nums[1], nums[2]));

        // pick first one, thus not allow to pick the last one
        std::vector<int> memo (nums.size() + 1, -1);
        memo[0] = 0;
        memo[1] = nums[0];
        memo[2] = nums[0]>nums[1] ? nums[0] : nums[1];
        memo[3] = std::max(nums[0], std::max(nums[1], nums[2]));

        int max1 = rob_iter(nums, 0, nums.size()-2, memo);
        int max2 = rob_iter(nums, 1, nums.size()-1, memo);
    
        return std::max(max1, max2);
    }
private:
    int rob_iter(const std::vector<int>& nums, int startIdx, int endIdx, std::vector<int>& memo) {

        int prevSkip = 0, prevRob = 0;
        int currSkip, currRob;

        for (int i=startIdx; i<=endIdx; ++i)
        {
            currSkip = std::max(prevSkip, prevRob);     // choose what's more either previously skipped, or previously robbed   
            currRob = nums[i] + prevSkip;               // keep accumulate the current rob amount which must include previously skipped
            prevSkip = currSkip;
            prevRob = currRob;
        }

        // return what's more between current skip, or current rob
        return std::max(currSkip, currRob);
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
