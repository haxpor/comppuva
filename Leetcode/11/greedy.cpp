/**
 * Problem 11 - https://leetcode.com/problems/container-with-most-water/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Max area
 * ... and so on for TC#2 and on
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        const int size = height.size();

        // at least, there should be 2 lines
        if (size < 2)
            return 0;

        // compute right away for size fit
        if (size == 2)
            return std::min(height[0], height[1]);

        int maxArea = 0;
        int left = 0;
        int right = size-1;
        while (left < right)
        {
            maxArea = std::max(maxArea, std::min(height[left], height[right]) * (right-left));

            // move left/right to maximize the area
            if (height[left] < height[right])
                ++left;
            else if (height[left] > height[right])
                --right;
            else
                // if equal, choose left
                ++left;
        }
        return maxArea;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases
    infile.ignore();

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile, line);
        std::istringstream lineStream(line);
        std::vector<int> inputs;

        int num;

        // get list of input numbers
        while (lineStream >> num)
        {
            inputs.push_back(num);
        }

        int expectArea;
        infile >> expectArea;

        // compute
        int outArea = sol.maxArea(inputs);
        if (outArea == expectArea)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, outArea, expectArea);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, outArea, expectArea);
            std::exit(1);
        }
    }

    infile.close();

    return 0;
}
