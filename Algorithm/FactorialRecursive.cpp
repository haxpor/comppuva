/**
 * Implementation of factorial recursively.
 */

#include <iostream>

static int Factorial(int n)
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
    std::cout << Factorial(10) << std::endl;

    return 0;
}
