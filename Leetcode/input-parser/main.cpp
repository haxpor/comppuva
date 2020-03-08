/**
 * Array Input parser for Leetcode's problems input.
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Expect number
 * TC#2 ... and so on
 *
 * Time complexity: <to-be-filled>
 * Space complexity: <to-be-filled>
 */
#include <cassert>
#include <iostream>
#include <vector>
#include "ArrayInputParser.h"

int main()
{
    ArrayInputParser parser;
    // 1d vector test
    {
        std::vector<int> out = parser.parse<int>("[]");
        assert(out.size() == 0 && "size of array should be 0");
    }
    {
        std::vector<int> out = parser.parse<int>("[1]");
        assert(out.size() == 1 && "size of array should be 1");
        assert(out[0] == 1 && "first element should be 1");
    }
    {
        std::vector<int> out = parser.parse<int>("[1,2,3,4]");
        assert(out.size() == 4 && "size of array should be 4");
        assert(out[0] == 1 && "first element should be 1");
        assert(out[1] == 2 && "first element should be 2");
        assert(out[2] == 3 && "first element should be 3");
        assert(out[3] == 4 && "first element should be 4");
    }
    {
        std::vector<char> out = parser.parse<char>("[\"1\",\"2\"]");
        assert(out.size() == 2 && "size of array should be 2");
        assert(out[0] == '1' && "first element should be '1'");
        assert(out[1] == '2' && "first element should be '2'");
    }

    // 2d vector tests
    {
        std::vector<std::vector<int>> out = parser.parse<std::vector<int>>("[[]]");
        assert(out.size() == 1 && "size of 2d-array should be 1");
    }
    {
        std::vector<std::vector<int>> out = parser.parse<std::vector<int>>("[[1],[2,3]]");
        assert(out.size() == 2 && "out.size() should be 2");
        assert(out[0].size() == 1 && "out[0].size() should be 1");
        assert(out[1].size() == 2 && "out[1].size() should be 2");
        assert(out[0][0] == 1 && "out[0][0] should be 1");
        assert(out[1][0] == 2 && "out[1][0] should be 2");
        assert(out[1][1] == 3 && "out[1][0] should be 3");
    }
    {
        std::vector<std::vector<int>> out = parser.parse<std::vector<int>>("[[1,2],[3,4]]");
        assert(out.size() == 2 && "size of 2d-array should be 2");
        assert(out[0].size() == 2 && "size of out[0] should be 2");
        assert(out[1].size() == 2 && "size of out[1] should be 2");
        assert(out[0][0] == 1 && "out[0][0] should be 1");
        assert(out[0][1] == 2 && "out[0][1] should be 2");
        assert(out[1][0] == 3 && "out[0][0] should be 3");
        assert(out[1][1] == 4 && "out[0][1] should be 4");
    }
    {
        std::vector<std::vector<char>> out = parser.parse<std::vector<char>>("[[\"1\",\"1\",\"0\"],[\"1\",\"1\",\"0\"]]");
        assert(out.size() == 2 && "size of 2d-array should be 2");
        assert(out[0].size() == 3 && "size of out[0] should be 3");
        assert(out[1].size() == 3 && "size of out[1] should be 3");
        assert(out[0][0] == '1');
        assert(out[0][1] == '1');
        assert(out[0][2] == '0');
        assert(out[1][0] == '1');
        assert(out[1][1] == '1');
        assert(out[1][2] == '0');
    }
    return 0;
}
