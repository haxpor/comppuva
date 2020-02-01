// Problem: https://leetcode.com/problems/two-sum/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        vector<int> ret;
        unordered_map<int, int> indicesLookup;

        int size = nums.size();

        for (int i=0; i<size; ++i)
        {
            indicesLookup[nums[i]] = i;   
        }

        for (int i=0; i<size; ++i)
        {
            auto itFind = indicesLookup.find(target - nums[i]);
            if (itFind != indicesLookup.end() && itFind->second != i) {
                // found
                ret.push_back(i);
                ret.push_back(itFind->second);
                return ret;
            }

        }
        return ret;
    }
};

int main()
{
    // input
    vector<int> inputs = {3,2,4};
    int target = 6;

    Solution sol;
    vector<int> out = sol.twoSum(inputs, target);

    // validate the result
    assert(out[0] == 1);
    assert(out[1] == 2);

    return 0;
}
