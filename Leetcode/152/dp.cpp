// Problem 152 - https://leetcode.com/problems/maximum-product-subarray/
#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public:
    int maxProduct(std::vector<int>& nums)
    {
        if (nums.size() == 0)
            return 0;

        const int size = nums.size();

        int max = nums[0];
        int min = nums[0];
        int fPrevMin = nums[0];
        int fPrevMax = nums[0];
        int maxResult = nums[0];

        for (int i=1; i<size; ++i)
        {
            max = std::max(nums[i], std::max(fPrevMax * nums[i], fPrevMin * nums[i]));
            min = std::min(nums[i], std::min(fPrevMax * nums[i], fPrevMin * nums[i]));

            maxResult = std::max(max, maxResult);

            fPrevMax = max;
            fPrevMin = min;
        }

        return maxResult;
    }
};

int main()
{
    std::vector<int> inputs = {2,3,-2,4};
    Solution sol;
    int out = sol.maxProduct(inputs);
    assert(out == 6);
    return 0;
}
