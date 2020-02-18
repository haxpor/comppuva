/**
 * Problem 55 - Jump Game - https://leetcode.com/problems/jump-game/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Expect number
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
    bool canJump(std::vector<int>& nums) {
        if (nums.size() == 0)
            return false;
        if (nums.size() == 1)
            return true;

        std::vector<int> memo (nums.size()+1, -1);

        return solve(nums, 0, memo);
    }
private:
    bool solve(const std::vector<int>& nums, int startIdx, std::vector<int>& memo) {
        if (startIdx == nums.size()-1)
            return true;
        if (startIdx >= nums.size())
            return false;
        if (memo[startIdx] != -1)
            return memo[startIdx] ? true : false;

        // iterate through all jump amount
        int maxJumpAmount = nums[startIdx];

        // if there is no more jump possible, thus not possible
        if (startIdx < (nums.size()-1) && maxJumpAmount == 0)
            return false;

        bool possible = false;
        for (int jm=1; jm<=maxJumpAmount; ++jm) {
            if (solve(nums, startIdx+jm, memo)) {
                possible = true;
                break;
            } 
        }
        memo[startIdx] = possible;
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

        // get the expect output
        bool expect;
        infile >> std::boolalpha >> expect;
        infile.ignore();

        // compute
        bool out = sol.canJump(inputs);
        if (out == expect)
        {
            std::cout << "[Success #" << i << "] Output = " << std::boolalpha << out << ", Expect = " << expect << '\n';
        }
        else
        {
            std::cout << "[Failed #" << i << "] Output = " << std::boolalpha << out << ", Expect = " << expect << '\n';
        }
    }

    infile.close();
    std::cout.flush();

    return 0;
}
