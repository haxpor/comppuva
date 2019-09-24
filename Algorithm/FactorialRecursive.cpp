/**
 * Implementation of factorial recursively.
 */

#include <iostream>

typedef long long int FactInt;

static FactInt Factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n * Factorial(n - 1);
}

int main()
{
    std::cout << Factorial(0) << std::endl;
    std::cout << Factorial(5) << std::endl;
    std::cout << Factorial(12) << std::endl;
    std::cout << Factorial(7) << std::endl;
    std::cout << Factorial(8) << std::endl;

    return 0;
}
