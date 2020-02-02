// Problem 53 - Maximum Subarray
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        const int size = nums.size();
        int fPrev = nums[0];
        int maxSum = nums[0];

        for (int i=1; i<size; ++i)
        {
           fPrev = max(fPrev + nums[i], nums[i]);
           maxSum = max(maxSum, fPrev);
        }

        return maxSum;
    }
};

int main()
{
    vector<int> inputs = {-2,1,-3,4,-1,2,1,-5,4};
    Solution sol;
    int out = sol.maxSubArray(inputs);

    assert(out == 6);
    return 0;
}
