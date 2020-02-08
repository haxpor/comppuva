// Problem: 153 - https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
#include <vector>
#include <cassert>
#include <iostream>

class Solution
{
public:
    int findMin(std::vector<int>& nums) {
        const int size = nums.size();

        if (size == 0)
            return 0;
        if (size == 1)
            return nums.front();

        for (int i=0; i<size-1; ++i)
        {
            if (nums[i] > nums[i+1])
                return nums[i+1];
        }

        return nums[0];
    }
};

int main()
{
    std::vector<int> inputs = {1,2};

    Solution sol;
    int out = sol.findMin(inputs);

    assert(out == 1);
    return 0;
}
