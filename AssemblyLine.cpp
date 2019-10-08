/**
 * Practice assembly line scheduling problem - https://www.geeksforgeeks.org/assembly-line-scheduling-dp-34/
 *
 * Note:
 *  I studied the problem, then trying to map the thought process of this type of dynamic programming problem.
 *  Then code the solution myself. Thanks to great explanation on such link as well.
 *
 * Problem:
 *  Calculate the minimum time required to finish the job at the assembly line.
 */

#include <iostream>
#include <algorithm>

#define NUM_LINE 2
#define NUM_STATION 4

// for convenient preventing confusion
#define FIRST_LINE 0
#define SECOND_LINE 1

/**
 * Find minimum possible required time to finish at the assembly line.
 */
static int findMinTime(const int tentry[NUM_LINE], const int tdiff[NUM_LINE][NUM_STATION],
                       const int t[NUM_LINE][NUM_STATION], const int tend[NUM_LINE])
{
    int t1[NUM_STATION] = {0}, t2[NUM_STATION] = {0};

    // starting
    t1[0] = tentry[0] + t[0][0];
    t2[0] = tentry[1] + t[1][0];

    // stations
    for (int s=1; s<NUM_STATION; ++s)
    {
        t1[s] = std::min(t1[s-1] + t[0][s], t2[s-1] + t[0][s] + tdiff[1][s]);
        t2[s] = std::min(t1[s-1] + t[1][s] + tdiff[0][s], t2[s-1] + t[1][s]);
    }
    
    // at the end of the assembly line
    return std::min(tend[0] + t1[NUM_STATION-1], tend[1] + t2[NUM_STATION-1]);
}

/**
 * Find minimum possible time required to reach station s (indexed-based).
 * If input s is s+1, then this will find minimum possible time required to finish the assembly line.
 */
static int findMinTime_recur(const int tentry[NUM_LINE], const int tdiff[NUM_LINE][NUM_STATION],
                             const int t[NUM_LINE][NUM_STATION], const int tend[NUM_LINE], int line, int s)
{
    if (s == 0)
    {
        return tentry[line] + t[line][s];
    }
    else
    {
        if (line == FIRST_LINE)
            return std::min(t[FIRST_LINE][s] + findMinTime_recur(tentry, tdiff, t, tend, FIRST_LINE, s-1),
                            t[FIRST_LINE][s] + tdiff[SECOND_LINE][s] + findMinTime_recur(tentry, tdiff, t, tend, SECOND_LINE, s-1));
        else
            return std::min(t[SECOND_LINE][s] + tdiff[FIRST_LINE][s] + findMinTime_recur(tentry, tdiff, t, tend, FIRST_LINE, s-1),
                            t[SECOND_LINE][s] + findMinTime_recur(tentry, tdiff, t, tend, SECOND_LINE, s-1));
    }
}

static int findMinTimeWrapper_recur(const int tentry[NUM_LINE], const int tdiff[NUM_LINE][NUM_STATION],
                                    const int t[NUM_LINE][NUM_STATION], const int tend[NUM_LINE])
{
    int cost1 = findMinTime_recur(tentry, tdiff, t, tend, FIRST_LINE, NUM_STATION-1) + tend[FIRST_LINE];
    int cost2 = findMinTime_recur(tentry, tdiff, t, tend, SECOND_LINE, NUM_STATION-1) + tend[SECOND_LINE]; 
    return std::min(cost1, cost2);
}

int main()
{
    // entry time needed to enter the line at the first station
    int tentry[NUM_LINE] = {10, 12};
    // time needed to switch from one station to another on different line
    int tdiff[NUM_LINE][NUM_STATION] = {
        {0, 7, 4, 5},
        {0, 9, 2, 8}
    };  
    // time needed to switch from one station to the next in the same line
    int t[NUM_LINE][NUM_STATION] = {
        {4, 5, 3, 2},
        {2, 10, 1, 4}
    };
    // time needed to ended the assembly line at the end
    int tend[NUM_LINE] = {18, 7};

    // non-recursive memoization version
    std::cout << findMinTime(tentry, tdiff, t, tend) << std::endl;
    // recursive version
    std::cout << findMinTimeWrapper_recur(tentry, tdiff, t, tend) << std::endl;
    return 0;
}
