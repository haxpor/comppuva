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
 * Time complexity: <to-be-filled>
 * Space complexity: <to-be-filled>
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "ArrayInputParser.h"

class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
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
        std::vector<std::vector<int>> preRequisites = aparser.parse2(line); // parse 2d-vector

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
