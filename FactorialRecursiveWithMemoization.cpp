/**
 * Implementation of factorial with memoization.
 *
 * The first calls to Factorial(N) will be memorized its result into memo for later calls.
 * If later calls is Factorial(M) wheres M <= N then the result will be fetched from memo directly (cache hit).
 * Otherwise the additional computation will be made which is not to re-calculate the previous results
 * again unnecessary.
 */

#include <iostream>
#include <algorithm>

// see https://en.cppreference.com/w/cpp/language/types
// for types in C++
typedef long long int FactInt;

// fixed-size memo lookup
// note: brace initializer doesn't work with non-zero value, use other ways to do it instead i.e. std::fill
FactInt memo[1000];

// undefined behavior is called of negative number
static FactInt Factorial(int n)
{
    if (memo[n] != -1)
        return memo[n];
    else if (n == 0)
    {
        memo[0] = 1;
        return 1;
    }
    else
    {
        FactInt r = n * Factorial(n - 1);
        memo[n] = r;
        return r;
    }
}

int main()
{
    // initialize all values inside memo to -1 to indicates results are empty
    std::fill(memo, memo+1000, -1);

    std::cout << Factorial(0) << std::endl;
    std::cout << Factorial(5) << std::endl;
    std::cout << Factorial(12) << std::endl;
    std::cout << Factorial(7) << std::endl;     // the result was cached, this return directly without re-calcution
    std::cout << Factorial(9) << std::endl;     // same as previous line
    return 0;
}
