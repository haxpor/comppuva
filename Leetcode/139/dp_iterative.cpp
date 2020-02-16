/**
 * Problem 139 - Word Break - https://leetcode.com/problems/word-break
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input string to determine whether it can be broken into words according to input dict
 * TC#1 white space separated for words in dictionary
 * TC#1 Expect result whether input string can be broken into words. Either true or false string.
 * TC#2 ...
 *
 * Time complexity: O(N^2) 
 * Space complexity: O(N) 
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <unordered_set>

class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        if (s.size() == 0)
            return false;

        std::vector<bool> dp (s.size() + 1, false);
        dp[0] = true;       // to satisfy the loop checking
        std::unordered_set<std::string> wordSet (wordDict.begin(), wordDict.end());

        for (int i=1; i<=s.size(); ++i) {
            for (int j=0; j<s.size(); ++j) {
                if (dp[j]) {
                    std::string ss = s.substr(j, i-j);
                    if (wordSet.count(ss) == 1) {       // distinct element in dict
                        dp[i] = true;
                        break;  // break now as it has breaking word now
                    }
                }
            }
        }
        return dp[s.size()];
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
        // get input string
        std::string inputString;
        infile >> inputString;
        infile.ignore();

        // get words in dictionary
        std::getline(infile, line);
        std::istringstream lineStream(line);
        std::vector<std::string> dict;

        // get list of input words
        std::string word;
        while (lineStream >> word)
        {
            dict.push_back(word);
        }

        // get expect result
        bool expect;
        infile >> std::boolalpha >> expect;

        // compute
        bool out = sol.wordBreak(inputString, dict);
        if (out == expect)
        {
            std::cout << "[Success #" << i << "] Output = " << std::boolalpha << out << ", Expect = " << expect << '\n';
        }
        else
        {
            std::cout << "[Failed #" << i << "] Output = " << std::boolalpha << out << ", Expect = " << expect << '\n';
        }
    }

    infile.close();

    return 0;
}
