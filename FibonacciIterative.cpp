/**
 * Implementation of Fibonaaci algorithm in iterative (with Tabulation).
 */

#include <iostream>

#define MEMO_SIZE 100

int memo[MEMO_SIZE];

static int Fibonacci(int n)
{
    // check cache
    if (memo[n] != -1)
    {
        return memo[n];
    }
    // end-point cases
    // note: remember this is iterative, in this single call, we need to make sure all end-point cases
    // are set properly
    else if (n == 0)
    {
        memo[0] = 0;
        return 0;
    }
    else if (n == 1)
    {
        memo[0] = 0;        // also set the end-point case for x<n
        memo[1] = 1;
        return 1;
    }
    // computational work
    //  - find additional work to be done
    //  - work bottom-up then return
    else
    {
        // find location for additional computation to be done
        int k = n-1;
        for (;k>=0; --k)
        {
            if (memo[k] != -1)
            {
                k = k+1;
                break;
            }
        }

        for (int i=k; i<=n; ++i)
            memo[i] = memo[i-1] + memo[i-2];

        return memo[n];
    }
}

int main()
{
    std::fill(memo, memo+MEMO_SIZE, -1);

    std::cout << Fibonacci(1) << std::endl;
    std::cout << Fibonacci(5) << std::endl;
    std::cout << Fibonacci(10) << std::endl;
    std::cout << Fibonacci(12) << std::endl;
    return 0;
}
