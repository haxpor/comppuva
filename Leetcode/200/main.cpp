/**
 * Problem 200 - Number of Islands https://leetcode.com/problems/number-of-islands/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of array with element of '1' or '0' to indicate land and water
 * TC#1 Expect number of islands
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
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.size() == 0)
            return 0;    

        M = grid.size();
        N = grid[0].size();

        std::vector<std::vector<bool>> visited (M, std::vector<bool>(N, false));
        int count = 0;

        for (int row=0; row<M; ++row) {
            for (int col=0; col<N; ++col) {
                if (grid[row][col] == '1' && !visited[row][col]) {
                    ++count;
                    dfs(grid, visited, row, col);
                }
            }
        }

        return count;
    }
private:
    int M;
    int N;

    void dfs(const std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, int row, int col) {
        if (row < 0 || col < 0 || row >= M || col >= N || visited[row][col] || grid[row][col] == '0')
            return;

        visited[row][col] = true;

        dfs(grid, visited, row+1, col);     // up
        dfs(grid, visited, row, col+1);     // right
        dfs(grid, visited, row-1, col);     // down
        dfs(grid, visited, row, col-1);     // left
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
        // get input grid
        std::getline(infile, line);
        std::vector<std::vector<char>> grid = aparser.parse<std::vector<char>>(line);

        // get expect number of islands
        int expectNumberOfIslands;
        infile >> expectNumberOfIslands;
        infile.ignore();

        // compute
        int out = sol.numIslands(grid);
        if (out == expectNumberOfIslands)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, out, expectNumberOfIslands);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out, expectNumberOfIslands);
        }
    }

    infile.close();

    return 0;
}
