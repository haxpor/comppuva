/**
 * Problem 10991 of UVa
 * Slightly adapted and mainly used for studying from Competitive Programming 3 by Steven & Felix.
 */

#include <algorithm>        // if you have problems with this C++ code,
#include <cmath>            // consult your progrmaming text books first...
#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_TEAM 8
#define MAX_STUDENT (2 * MAX_TEAM)

/* Forming Quiz Teams, the solution for UVa 10911 above */
// using global variables is a bad software engineering practices.
int N, target;          // but it is OK for competitive programming

// the dimension size of dist can be optimized to only the maximum number of students as per constriant
// for memo, as we want it to represent the bit string for setting flags, then 1 << 16 = 2^16
// note that max N = 8
double dist[MAX_STUDENT][MAX_STUDENT], memo[1 << MAX_STUDENT]; 

double matching(int bitmask)            // DP state = bitmask
{
    // we initialize 'memo' with -1 in the main function
    // this state has been computed before
    // simply lookup the memo table
    if (memo[bitmask] -(-1.0) >= std::numeric_limits<double>::epsilon())
        return memo[bitmask];
    // all students are already matched
    // the cost is 0
    if (bitmask == target)
        return memo[bitmask] = 0;

    // initialize with a arbitrary large value
    double ans = 2000000000.0;

    int p1, p2;
    for (p1=0; p1<2*N; ++p1)
        if (!(bitmask & (1 << p1)))
            break;                              // find the first bit that is off
    for (p2=p1+1; p2<2*N; ++p2)                 // then try to match p1
        if(!(bitmask & (1 << p2)))              // with another bit p2 that is also off
            ans = min(ans, dist[p1][p2] + matching(bitmask | (1 << p1) | (1 << p2)));   // pick the minimum
                                                                                        // bitmask | (1 << p1) | 1 << p2) is the location of bit-string to locate

    memo[bitmask] = ans;                 // store result in a memo table and return
    return ans;
}

int main()
{
    int i, j, caseNo = 1, x[MAX_STUDENT], y[MAX_STUDENT];
    // freopen("10911.txt", "r", stdin);        // redirect input file to stdin
                                                // note: not recommended to use freopen() as there's no
                                                // portable way to set back the original stdin
                                                // anyway no problem here as scanf() is suffice
    
    while (scanf("%d", &N), N)
    {
        for (i=0; i<2*N; ++i)
            scanf("%*s %d %d", &x[i], &y[i]);   // %*s skip names
        // row, then column, operate only the upper right triangle of table
        // as another half would be duplicated of it
        for (i=0; i<2*N-1; ++i)                 // build pair-wise distance table
            for (j=i+1; j<2*N; ++j)             // have you used 'hypot' before?
                dist[i][j] = dist[j][i] = hypot(x[i] - x[j], y[i] - y[j]);

        // use DP to solve min weighted perfect matching on small general graph
        // see bipartite minimum cost perfect matching
        for (i=0; i < (1 << MAX_STUDENT); ++i)
            memo[i] = -1.0;                     // set -1 to all cells
        // the last bit position is the integer represent the whole bit string - 1
        // or think in index-based
        target = (1<<(2*N)) - 1;
        printf("Case %d: %.2lf\n", caseNo++, matching(0));
    }

    return 0;
}
