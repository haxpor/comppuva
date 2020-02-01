// Problem: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        const int size = prices.size();
        int maxProfit = 0;

        for (int i=0; i<size; ++i)
        {
            for (int j=i; j<size; ++j)
            {
                int currProfit = prices[j] - prices[i];
                if (currProfit > maxProfit)
                    maxProfit = currProfit;
            }
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
