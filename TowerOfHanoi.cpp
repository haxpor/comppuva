/**
 * Solution on Tower of Hanoi problem.
 *
 * Note:
 *  - It's easier to think in terms of moving N-1 disks from starting rod to destination rod.
 *    This makes it easy to come up with algorithm to implement in code.
 *    Lastly when there is just 1 disk left, move it to the destination rod.
 *    Especially see this explanation https://www.geeksforgeeks.org/c-program-for-tower-of-hanoi/.
 *
 *  - The reason why print function call needs to be between two recursive function calls
 *    is because of print function call is also as part of the procedure but it's just printing something
 *    out. See https://www.cs.cmu.edu/~cburch/survey/recurse/hanoiimpl.html.
 *
 */
#include <iostream>

/**
 * Move n disks from rod 'from' to rod 'to' with auxilary rod 'aux'.
 * Rods are represented as characters.
 */
static void towerHanoiMove(int n, char from, char to, char aux)
{
    // typical implementation will have n == 1 check, the following might seem weird
    // but for us to have only one place in printing out
    if (n > 0)
    {
        // the whole procedure can be described as a big picture of 3 steps as follows
        // move n-1 disks from 'A' to 'B'
        towerHanoiMove(n-1, from, aux, to);
        // now we're left with the last disk in 'A', then move it to 'C'
        std::cout << "move disk " << n << " from " << from << " to " << to << std::endl;
        // move n-1 disks from 'B' to 'C'
        towerHanoiMove(n-1, aux, to, from);
    }
}

int main()
{
    // the problem set has 4 disks with objective to move from rod 'A' to 'C' with auxilary at rod 'B'.
    towerHanoiMove(3, 'A', 'C', 'B');
    return 0;
}
