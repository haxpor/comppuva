/**
 * Finding shortest paths via dynamic programming.
 * Read more about this at https://medium.com/@tiagot/dynamic-programming-an-induction-approach-b5c5e73c4a19
 * by Tiago.
 *
 * The key topics that might be of interest is
 *  - Induction - https://www.youtube.com/watch?v=uK5yvoXnkSk
 *
 * Rules
 *  - Only can move to the right, or move down
 *
 * Objective
 *  - Find the shortest path from top-left corner to the bottom-right corner of cells.
 */

#include <iostream>
#include <algorithm>
#include <iomanip>

#define CELLSIZE 6
#define DEBUG 0

static int findShortestPath(const int cells[CELLSIZE][CELLSIZE])
{
    int stp[CELLSIZE][CELLSIZE];

    // the base case, the starting location needs not depend on other sub-problem
    stp[0][0] = cells[0][0];
    for (int i=1; i<CELLSIZE; ++i)
    {
        // fill entire first row
        stp[0][i] = stp[0][i-1] + cells[0][i];
        // fill entire first column
        stp[i][0] = stp[i-1][0] + cells[i][0];
    }

    // notice that no matter the target location we want to find its shortest path from the
    // top-left corner, our destination location will locate at the bottom-right corner always
    // with addition that we reduce the map size as part of shortest path calculation 
    for (int i=1; i<CELLSIZE; ++i)
    {
        for (int j=1; j<CELLSIZE; ++j)
        {
            stp[i][j] = std::min(stp[i-1][j], stp[i][j-1]) + cells[i][j];
        }
    }

    return stp[CELLSIZE-1][CELLSIZE-1];
}

int main()
{
    int cells[CELLSIZE][CELLSIZE] = {
        {5, 3, 2, 1, -2, 7},
        {1, 7, -3, 3, 5, 4},
        {4, 4, -2, 8, 1, -3},
        {8, -1, 7, 0, 5, 2},
        {4, 6, -3, 3, -4, 7},
        {-5, 3, -2, 6, 9, 2}
    };

#if DEBUG
    for (int i=0; i<CELLSIZE; ++i)
    {
        for (int j=0; j<CELLSIZE; ++j)
        {
            std::cout << std::setw(2) << cells[i][j] << " | ";
        }
        std::cout << "\n";
    }
#endif

    std::cout << "Shortest path: " << findShortestPath(cells) << "\n";
    std::cout.flush();

    return 0;
}
