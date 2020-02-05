// Problem 152 - https://leetcode.com/problems/maximum-product-subarray/
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution
{
public:
    int maxProduct(vector<int>& nums)
    {
        const int size = nums.size();

        int fPrev = nums[0];
        int max = nums[0];

        for (int i=1; i<size; ++i)
        {
            fPrev = fPrev * nums[i];
            max = std::max(max, fPrev);
        }

        return max;
    }
};

int main()
{
    vector<int> inputs = {2,-5,-2,-4,3};
    Solution sol;
    int out = sol.maxProduct(inputs);
    assert(out == 24);
    return 0;
}
