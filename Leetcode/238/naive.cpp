// Problem 238 - https://leetcode.com/problems/product-of-array-except-self/
// This will be Time Limit Exceeded
#include <vector>
#include <cassert>

using namespace std;

class Solution
{
public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        const int size = nums.size();

        vector<int> products;
        products.resize(size);

        for (int i=0; i<size; ++i)
        {
            bool first = true;

            for (int ei=0; ei<size; ++ei)
            {
                if (i != ei)
                {
                    if (first)
                    {
                        products[i] = nums[ei];
                        first = false;
                    }
                    else
                    {
                        products[i] *= nums[ei];
                    }
                }
            }
        }

        return products;
    }
};

int main()
{
    vector<int> inputs = {1,2,3,4};

    Solution sol;
    vector<int> out = sol.productExceptSelf(inputs);

    assert(out[0] == 24);
    assert(out[1] == 12);
    assert(out[2] == 8);
    assert(out[3] == 6);
    
    return 0;
}
