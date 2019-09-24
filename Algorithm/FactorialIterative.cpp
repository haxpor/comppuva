/**
 * Implementation of factorial iteratively (tabulation).
 */

#include <iostream>

// see https://en.cppreference.com/w/cpp/language/types
// for types in C++
typedef long long int FactInt;

// fixed-size memo lookup
// note: brace initializer doesn't work with non-zero value, use other ways to do it instead i.e. std::fill
FactInt memo[1000];

static FactInt Factorial(int n)
{
    // checking from cache should be prioritized
    if (memo[n] != -1)
        return memo[n];
    else if (n == 0)
    {
        memo[0] = 1;
        return 1;
    }
    else
    {
        // find the location onwards on where to do addition calculation
        int k = n-1;
        for (; k>=0; --k)
        {
            if (memo[k] != -1)
            {
                k = k + 1;
                break;
            }
        }

        // work bottom-up
        for (int i=k; i<=n; ++i)
            memo[i] = i * memo[i-1];

        return memo[n];
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
