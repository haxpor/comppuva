// Problem 217 - https://leetcode.com/problems/contains-duplicate/
// This will be Time Limit Exceeded
#include <vector>
#include <cassert>

using namespace std;

class Solution
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        const int size = nums.size();
        for (int i=0; i<size; ++i)
        {
            int base = nums[i];
            for (int j=i+1; j<size; ++j)
            {
                if (base == nums[j])
                    return true;
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
