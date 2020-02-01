// Problem: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        const int size = prices.size();
        int minPrice = numeric_limits<int>::max();
        int maxProfit = 0;

        for (int i=0; i<size; ++i)
        {
            int price = prices[i];
            if (minPrice > price)
                minPrice = price;
            else if (price - minPrice > maxProfit)
                maxProfit = price - minPrice;
        }

        return maxProfit;
    }
};

int main()
{
    vector<int> inputs = {7,1,5,3,6,4};

    Solution sol;
    int out = sol.maxProfit(inputs);

    assert(out == 5);

    return 0;
}
