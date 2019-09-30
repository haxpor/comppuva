#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

int p, q, r, s, t, u;

static double f(double x)
{
    return p * std::exp(-x) + q * std::sin(x) + r * std::cos(x) + s * std::tan(x) + t * std::pow(x, 2) + u;
}

static double bisection()
{
    double low = 0.0, high = 1.0;
    while (low + std::numeric_limits<double>::epsilon() < high)
    {
        double x = (low + high) / 2.0;
        if (f(low) * f(x) <= 0.0)
            high = x;
        else
            low = x;
    }
    return (low+high) / 2.0;
}

int main()
{
    while (!std::cin.eof())
    {
        std::cin >> p >> q >> r >> s >> t >> u;
        // in case of reading past the last line
        if (std::cin.fail())
            break;

        if (f(0) * f(1) > 0)
            std::cout << "No solution\n";
        else
            std::cout << std::fixed << std::setprecision(4) << bisection() << '\n';
    }

    std::cout.flush();
    
    return 0;
}
