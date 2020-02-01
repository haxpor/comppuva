// Problem 217 - https://leetcode.com/problems/contains-duplicate/
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        unordered_map<int, int> lookup;

        const int size = nums.size();

        for (int i=0; i<size; ++i)
        {
            auto search = lookup.find(nums[i]);
            if (search != lookup.end())
            {
                // found
                return true;
            }
            else
            {
                lookup[nums[i]] = i;
            }
        }

        return false;
    }
};

int main()
{
    vector<int> inputs = {1,1,1,3,3,4,3,2,4,2};

    Solution sol;
    bool out = sol.containsDuplicate(inputs);

    assert(out == true);

    return 0;
}
