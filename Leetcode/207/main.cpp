/**
 * Problem 207 - Course Schedule - https://leetcode.com/problems/course-schedule/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Total number of courses
 * TC#1 List of prerequisite pairs e.g. [0,1] which means to take course 0, you have to take course 1
 * TC#1 Expect boolean result in "true" or "false".
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(N)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include "ArrayInputParser.h"

// studying solution from https://leetcode.com/problems/course-schedule/discuss/517653/C%2B%2B-DFS-(98-16ms)
class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        if (numCourses >= 0 && numCourses <= 1)
            return true;

        // change graph representation
        std::vector<std::vector<int>> graph (numCourses);
        for (const auto& prElem : prerequisites) {
            graph[prElem[0]].push_back(prElem[1]);
        }
        
        std::vector<int> memo (numCourses);
        std::memset(memo.data(), -1, sizeof(int) * (numCourses));      // -1 for initial state, 1 for visited, and 2 for possible

        for (int i=0; i<numCourses; ++i) {
            if (memo[i] != -1)
                continue;       // already visited or independent
            if (!DFS(i, graph, memo))
                return false;
        }

        // all courses possible
        return true;
    }

private:
    bool DFS(int courseIdx, const std::vector<std::vector<int>>& pr, std::vector<int>& memo) {
        if (memo[courseIdx] == 2)
            return true;
        if (memo[courseIdx] == 1)
            return false;           // it is cycle

        memo[courseIdx] = 1;   // mark as visited

        for (const auto& dependedCourse : pr[courseIdx]) {
            if (!DFS(dependedCourse, pr, memo))
                return false;
        }

        memo[courseIdx] = 2;
        return true;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases

    Solution sol;
    ArrayInputParser aparser;

    for (int i=0; i<N; ++i)
    {
        // get number of courses
        int numCourse;
        infile >> numCourse;
        infile.ignore();

        // get pre-requisites courses
        std::getline(infile, line);
        std::vector<std::vector<int>> preRequisites = aparser.parse<std::vector<int>>(line); // parse 2d-vector

        // get expect result
        bool expect;
        infile >> std::boolalpha >> expect;

        // compute
        int out = sol.canFinish(numCourse, preRequisites); 
        if (out == expect)
        {
            std::printf("[Success #%d] Output = %s, Expect = %s\n", i, out ? "true" : "false", expect ? "true" : "false");
        }
        else
        {
            std::printf("[Failed #%d] Output = %s, Expect = %s\n", i, out ? "true" : "false", expect ? "true" : "false");
        }
    }

    infile.close();

    return 0;
}
