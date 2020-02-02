// Problem 53 - Maximum Subarray
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        const int size = nums.size();
        int currMaxSum = 0;
        int maxSum = numeric_limits<int>::min();

        for (int i=0; i<size; ++i)
        {
            if (currMaxSum >= 0)
            {
                currMaxSum += nums[i];
            }
            else
            {
                currMaxSum = nums[i];
            }

            maxSum = max(currMaxSum, maxSum);
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
