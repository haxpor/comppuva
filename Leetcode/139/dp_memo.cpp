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
        std::vector<int8_t> memo (s.size() + 1, -1);

        std::unordered_set<std::string> wordSet;
        for (const auto& w : wordDict) {
            wordSet.emplace(w);
        }

        return wordBreak_recur(s, 0, wordSet, memo);
    }

private:
    bool wordBreak_recur(const std::string& s, int startIdx, std::unordered_set<std::string>& wordSet, std::vector<int8_t>& memo) {
        if (startIdx == s.size())
            return true;

        if (memo[startIdx] != -1)
            return memo[startIdx];

        for (int i=startIdx+1; i<=s.size(); ++i) {
            std::string ss = s.substr(startIdx, i - startIdx);
            if (wordSet.count(ss) == 1) {       // contains() requires c++20
                if (wordBreak_recur(s, i, wordSet, memo))
                {
                    memo[startIdx] = 1;
                    return true;
                }
            }
        }

        memo[startIdx] = 0;
        return false;
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
