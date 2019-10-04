/**
 * Knight (chess) tour problem - https://www.geeksforgeeks.org/the-knights-tour-problem-backtracking-1/
 * Using backtracking
 *
 * Note:
 *  Studied the problem and approach used in the link, then implement in my own way.
 *
 * Analysis:
 *  Each move possibility of a knight on a chess board when moved, need to determine another 8 possibilities.
 *  Thus recursively costs upper bound O(N*N*(2^8)) = O(N^2).
 *
 *  The order of movement of a knight can be a factor for time used in the algorithm as well.
 *  As it needs to go from top-left to the bottom-right, it's best to search in clockwise-order
 *  not a counter-clockwise order as used in the program.
 */

#include <iostream>
#include <iomanip>

#define N 8
#define N2 N*N
#define CLOCKWISE_ORDER 0

static bool isSafe(int x, int y, const int sols[N][N])
{
    if (x >= 0 && x < N &&
        y >=0 && y < N &&
        sols[x][y] == -1)
        return true;
    else
        return false;
}

static bool findSol(int x, int y, int moveCount, int sols[N][N], const int xmove[8], const int ymove[8])
{
    if (moveCount == N2)
        return true;

    int nextX, nextY;
    for (int k=0; k<8; ++k)
    {
        nextX = x + xmove[k];
        nextY = y + ymove[k];

        // not yet visit => OK
        if (isSafe(nextX, nextY, sols))
        {
            sols[nextX][nextY] = moveCount;
            
            // terminated case is during move
            if (findSol(nextX, nextY, moveCount + 1, sols, xmove, ymove))
                return true;
            else
            {
                // this chosen path is not the correct solution
                // backtrack it
                sols[nextX][nextY] = -1;
            }           
        }
    }

    return false;
}

static void printSols(const int sols[N][N])
{
    for (int i=0; i<N; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            std::cout << " | " << std::setw(3) << sols[i][j];
        }
        std::cout << " | \n";
    }
}

int main()
{
    // note: the order will effect the running time of the program
    // from testing, counterclock-wise order runs faster in magnitude
    // clock-wise order
#if CLOCKWISE_ORDER
    const int xmove[] = {2, 1, -1, -2, -2, -1, 1, 2};
    const int ymove[] = {-1, -2, -2, -1, 1, 2, 2, 1};
#else
    // counterclock-wise order
    const int xmove[] = {2, 1, -1, -2, -2, -1, 1, 2};
    const int ymove[] = {1, 2, 2, 1, -1, -2, -2, -1};
#endif

    // this represents chess-board, and also solutions
    int sols[N][N];
    // mark as no solutions initially
    for (int i=0; i<N; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            sols[i][j] = -1;
        }
    }

    // start at 0,0, thus mark sols[0][0] with 0 (first step)
    sols[0][0] = 0; 

    if (findSol(0, 0, 1, sols, xmove, ymove))
        printSols(sols);
    else
        std::cout << "There is no solution\n";

    std::cout.flush();

    return 0;
}
