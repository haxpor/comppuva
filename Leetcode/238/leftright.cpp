// Problem 238 - https://leetcode.com/problems/product-of-array-except-self/
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

        vector<int> leftProducts;
        vector<int> rightProducts;
        vector<int> ret;

        leftProducts.resize(size);
        rightProducts.resize(size);
        ret.resize(size);

        leftProducts[0] = 1;
        for (int i=1; i<size; ++i)
        {
            leftProducts[i] = nums[i-1]*leftProducts[i-1];
        }

        rightProducts[size-1] = 1;
        for (int i=size-2; i>=0; --i)
        {
            rightProducts[i] = nums[i+1]*rightProducts[i+1];
        }

        for (int i=0; i<size; ++i)
        {
            ret[i] = leftProducts[i] * rightProducts[i];
        }
        return ret;
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
