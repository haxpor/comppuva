// Problem: 153 - https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>

class Solution
{
public:
    int findMin(std::vector<int>& nums) {
        const int size = nums.size();

        if (size == 0)
            return -1;
        else if (size == 1)
            return nums.front();

        int left = 0;
        int right = size-1;

        // all sorted case
        if (nums[right] > nums[left])
            return nums[left];

        while (left <= right)
        {
            int mid = left + (right-left)/2;

            // right-most comparison
            if (nums[mid] > nums[mid+1])
                return nums[mid + 1];

            // left-most comparison
            if (nums[mid-1] > nums[mid])
                return nums[mid];

            // progress left/right index
            if (nums[mid] > nums[0])
                left = mid+1;
            else
                right = mid - 1;
        }
        return -1;
    }
};

int main()
{
    std::vector<int> inputs = {3,1,2};

    Solution sol;
    int out = sol.findMin(inputs);

    assert(out == 1);
    return 0;
}
