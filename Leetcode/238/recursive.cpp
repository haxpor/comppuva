// Problem 238 - https://leetcode.com/problems/product-of-array-except-self/
// This is still Time Limit Exceeded (divide-and-conquer thus recursive still have time complexity of
// O(N^2).
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;

class Solution
{
private:
    int findProduct(int pivot, unordered_map<int, int>& lookup)
    {
        if (pivot == 0)
        {
            int left = 1;
            int right = lookup.size() - 1;      // constant time
            return _product(left, right, lookup);
        }
        else if (pivot == lookup.size()-1)
        {
            int left = 0;
            int right = lookup.size() - 2;
            return _product(left, right, lookup);
        }
        else
        {
            return _product(0, pivot-1, lookup) * _product(pivot+1, lookup.size()-1, lookup);
        }   
    }

    // divide-and-conquer
    int _product(int left, int right, unordered_map<int, int>& lookup)
    {
        if (right - left == 1)
        {
            return lookup[left] * lookup[right];
        }
        else if (right - left == 0)
        {
            return lookup[left];
        }
        else
        {
            int m = (left+right)/2;
            return _product(left, m, lookup) * _product(m+1, right, lookup);
        }
    }

public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        const int size = nums.size();

        vector<int> products;
        products.resize(size);

        unordered_map<int, int> lookup;
        for (int i=0; i<size; ++i)
        {
            lookup[i] = nums[i];
        }

        for (int i=0; i<size; ++i)
        {
            products[i] = findProduct(i, lookup);
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
