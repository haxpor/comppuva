/**
 * Following is the studying of tail-call optimization technique studying upon 
 * http://blog.moertel.com/posts/2013-05-11-recursive-to-iterative.html.
 *
 * In simply term, we are trying to convert the recursive call of tail-call category into iterative
 * call.
 */
#include <iostream>
#include <cassert>
#include <stack>

int factorial_recur(int n)
{
    if (n < 2)
        return 1;

    return n * factorial_recur(n-1);
}

int factorial_iterative(int n)
{
    if (n < 2)
        return 1;

    int nn = n;
    int res = 1;
    while (nn > 1)
    {
        res *= nn;
        --nn;
    }
    return res;
}

int factorial_stack(int n)
{
    if (n < 2)
        return 1;

    std::stack<int> stackN;
    int nn = n;
    while (nn > 1)
    {
        stackN.push(nn);
        --nn;
    }

    nn = n;
    int res = 1;
    while (nn > 1)
    {
        int localN = stackN.top();
        res *= localN;
        stackN.pop();
        --nn;
    }

    return res;
}

int main()
{
    assert(factorial_recur(5) == 120 && "wrong output from factorial_recur(5). Expect 120");
    assert(factorial_iterative(5) == 120 && "wrong output from factorial_iterative(5). Expect 120");
    assert(factorial_stack(5) == 120 && "wrong output from factorial_stack(5). Expect 120");
    return 0;
}
