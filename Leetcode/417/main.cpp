/**
 * Problem 417 - Pacific Atlantic Water Flow 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Array of Array of rows representing the matrix
 * TC#1 The expect output
 * TC#2 ... and so on
 *
 * Time complexity: O(M*N)
 * Space complexity: O(M*N)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "ArrayInputParser.h"

class Solution {
public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& matrix) {
        if (matrix.size() == 0)
            return {};

        M = matrix.size();
        N = matrix[0].size();
        
        std::vector<std::vector<bool>> pacific (M, std::vector<bool>(N, false));
        std::vector<std::vector<bool>> atlantic (M, std::vector<bool>(N, false));

        for (int col=0; col<N; ++col) {
            dfs(matrix, pacific, 0, col, -99);
            dfs(matrix, atlantic, M-1, col, -99);
        }

        for (int row=0; row<M; ++row) {
            dfs(matrix, pacific, row, 0, -99);
            dfs(matrix, atlantic, row, N-1, -99);
        }

        std::vector<std::vector<int>> result;
        for (int row=0; row<M; ++row) {
            for (int col=0; col<N; ++col) {
                if (pacific[row][col] && atlantic[row][col])
                    result.push_back({row, col});
            }
        }

        return result;
    }
private:
    int M;
    int N;

    // make a decision based on the specified `row` and `col` within the grid.
    void dfs(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>& ocean, int row, int col, int prevVal) {
        if (row < 0 || col < 0 || row >= M || col >= N || ocean[row][col] || matrix[row][col] < prevVal)
            return;

        ocean[row][col] = true;
        int baseVal = matrix[row][col];

        dfs(matrix, ocean, row+1, col, baseVal);    // up
        dfs(matrix, ocean, row, col+1, baseVal);    // right
        dfs(matrix, ocean, row-1, col, baseVal);    // down
        dfs(matrix, ocean, row, col-1, baseVal);    // left
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
    ArrayInputParser aparser;

    for (int i=0; i<N; ++i)
    {
        // read in matrix
        std::getline(infile, line);
        std::vector<std::vector<int>> matrix = aparser.parse<std::vector<int>>(line);

        // read expect result
        std::getline(infile, line);
        std::vector<std::vector<int>> expect = aparser.parse<std::vector<int>>(line);

        // compute
        std::vector<std::vector<int>> out = sol.pacificAtlantic(matrix);

        // order is not mandatory thus sort them both before comparing
        auto sortCompare = [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
        };
        std::sort(out.begin(), out.end(), sortCompare);
        std::sort(expect.begin(), expect.end(), sortCompare);

        if (out == expect)
        {
            std::printf("[Success #%d]\n", i);
        }
        else
        {
            std::printf("[Failed #%d] Output mismatch\n", i);
        }
    }

    infile.close();

    return 0;
}
