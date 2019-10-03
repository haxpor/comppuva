/**
 * Implementation of Fibonacci algorithm in recursive with memoization.
 */

#include <iostream>
#include <algorithm>

#define MEMO_SIZE 100

int memo[MEMO_SIZE];

static int Fibonacci(int n)
{
    // checking from case should be prioritized
    if (memo[n] != -1)
    {
        return memo[n];
    }
    else if (n == 0)
    {
        memo[0] = 0;
        return 0;
    }
    else if (n == 1)
    {
        memo[1] = 1;
        return 1;
    }
    else
    {
        int r = Fibonacci(n - 1) + Fibonacci(n - 2);
        memo[n] = r;
        return r;
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
