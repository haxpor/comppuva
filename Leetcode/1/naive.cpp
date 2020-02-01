// Problem: https://leetcode.com/problems/two-sum/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        vector<int> ret;
        int size = nums.size();

        for (int i=0; i<size; ++i)
        {
            for (int j=0; j<size; ++j)
            {
                if (i != j && nums[i] + nums[j] == target)
                {
                    ret.push_back(i);
                    ret.push_back(j);
                    return ret;
                }
            }
        }
        return ret;
    }
};

int main()
{
    // input
    vector<int> inputs = {2,7,11,15};
    int target = 9;

    Solution sol;
    vector<int> out = sol.twoSum(inputs, target);

    // validate the result
    assert(out[0] == 0 && out[1] == 1);

    return 0;
}
