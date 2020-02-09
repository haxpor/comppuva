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
 *
 * This solution got TLE. The solution still in order of O(N^3 * logN) due to equal_range is linear.
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
#include <unordered_map>
#include <set>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        const int size = nums.size();
        // need at least 3 elements to perform
        if (size < 3)
            return {};

        std::sort(nums.begin(), nums.end());

        // hashmap from value to index
        std::unordered_multimap<int, int> lookup;
        for (int i=0; i<size; ++i)
            lookup.insert(std::make_pair(nums[i], i));

        std::set<std::vector<int>> uniqueResults;       // take benefit of set to uniquely add new element

        for (int i=0; i<size; ++i)
        {
            for (int j=i+1; j<size; ++j)
            {
                int remaining = -nums[i] - nums[j];
                auto foundRange = lookup.equal_range(remaining);        // later I realized this doesn't help, it still costs O(N) for number of elements with that key
                for (auto it=foundRange.first; it!=foundRange.second; ++it)
                {
                    int k = it->second;
                    if (k > i && k > j)
                    {
                        std::vector<int> resultElem;
                        resultElem.push_back(nums[i]);
                        resultElem.push_back(nums[j]);
                        resultElem.push_back(nums[k]);
                        // uniquely add to set
                        uniqueResults.emplace(std::move(resultElem));
                        break;  // just one insertion is enough, otherwise will be duplicate
                    }
                }
            }
        }

        std::vector<std::vector<int>> results; 

        // prepare result in vector
        for (const auto& e : uniqueResults)
            results.emplace_back(std::move(e));

        return results;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases

    infile.ignore();    // need to ignore left-out byte (newline) from previously extraction operator

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

            // NOTE: You may have to modify the testcases.txt file to match the order of output results line by line
            // as we don't do iteration to find a match here.
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
