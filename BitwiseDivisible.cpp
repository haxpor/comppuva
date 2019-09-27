/**
 * Check if input number is divisible by N via bitwise operation.
 */

#include <iostream>
#include <cmath>
#include <cassert>

#define CHK(n,m) std::cout << std::boolalpha << n << " is divisible by " << m << ": " << isDivisible(n,m) << std::endl;

/**
 * Check if input number n is divisible by m.
 *
 */
static bool isDivisible(int n, int m)
{
    // there is also log10, and log (for natural base)
    double l = log2(m);
    assert(l-static_cast<long>(l) == 0);     // ensure that it has no decimal places
    long ll = static_cast<long>(l);
    return ((n >> ll) << ll == n);
}

int main()
{
    CHK(10,2)
    CHK(101,2)
    CHK(-32,16)
    CHK(32,16)
    CHK(200,8)
    CHK(200,2)
    CHK(1,16)
    return 0;
}
