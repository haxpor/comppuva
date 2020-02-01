// Problem 238 - https://leetcode.com/problems/product-of-array-except-self/
// optimize space complexity on top of leftright.cpp
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        const int size = nums.size();

        vector<int> products;
        products.resize(size);

        products[0] = 1;
        for (int i=1; i<size; ++i)
        {
            products[i] = nums[i-1]*products[i-1];
        }

        int r = 1;
        for (int i=size-1; i>=0; --i)
        {
            products[i] = products[i] * r;
            r *= nums[i];
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
