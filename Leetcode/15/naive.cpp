/**
 * Problem 15 - https://leetcode.com/problems/3sum/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Number of expected result
 * TC#1 Line by line expected result numbers separated by white space
 * TC#2 ... and so on
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        const int size = nums.size();
        // need at least 3 elements to perform
        if (size < 3)
            return std::vector<std::vector<int>>();

        std::vector<std::vector<int>> results;

        for (int i=0; i<size; ++i)
        {
            for (int j=0; j<size; ++j)
            {
                while (j == i)
                    ++j;

                for (int k=0; k<size; ++k)
                {
                    while ((k == j || k == i))
                        ++k;

                    if (nums[i] + nums[j] + nums[k] == 0)
                    {
                        std::vector<int> rs;
                        rs.push_back(nums[i]);
                        rs.push_back(nums[j]);
                        rs.push_back(nums[k]);           
                        results.emplace_back(rs);
                    }
                }
            }
        }

        // this will not be stable to be checked with expected output but result should be correct
        // sort each array element
        for (int i=0; i<results.size(); ++i)
        {
            std::sort(results[i].begin(), results[i].end());
        }
        // remove duplicates from outer-most vector
        std::stable_sort(results.begin(), results.end());
        auto last = std::unique(results.begin(), results.end());      // std::unique() return end iterator of new range
        results.erase(last, results.end());

        return results;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile.ignore(), line); // need to ignore left-out byte (newline) from previously extraction operator
                                             // otherwise, we will read newline instead
        std::istringstream lineStream(line);
        std::vector<int> inputs;

        int num;

        // get list of input numbers
        while (lineStream >> num)
        {
            inputs.push_back(num);
        }

        // get number of expected testcases
        int numExpect;
        infile >> numExpect;

        infile.ignore();

        // read all array of outputs from expected testcases
        std::vector<std::vector<int>> expectResults;
        for (int j=0; j<numExpect; ++j)
        {
            std::getline(infile, line);
            // reuse stringstream
            lineStream.str(line);
            lineStream.clear();

            std::vector<int> expResultElem;
            while (lineStream >> num)
            {
                expResultElem.push_back(num);
            }
            expectResults.emplace_back(expResultElem);
        }

        // compute
        const auto& results = sol.threeSum(inputs);
        if (results.size() != expectResults.size())
        {
            std::printf("[Failed #%d] Size of results not match. Output = %ld, Expect = %ld\n", i, results.size(), expectResults.size()); 
            std::exit(1);
        }
        // the size of user's results and expect results are the same
        for (int j=0; j<results.size(); ++j)
        {
            // check size
            if (results[j].size() != expectResults[j].size())
            {
                std::printf("[Failed #%d] Size of result array at index %d not match. Output = %ld, Expect = %ld\n", i, j, results[j].size(), expectResults[j].size());
                std::exit(1);
            }

            std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> mm = std::mismatch(results[j].begin(), results[j].end(), expectResults[j].begin(), expectResults[j].end());
            if (mm.first != results[j].end() && mm.second != results[j].end()) // if iterator is not at the end, then it matches
            {
                // there is at least one mismatch
                std::printf("[Failed #%d] Mismatch result for array index %d. Output = %d, Expect %d\n", i, j, *mm.first, *mm.second);
                std::exit(1);
            }
        }

        std::printf("[Success #%d]\n", i);
    }

    infile.close();

    return 0;
}
