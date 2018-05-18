#include "common.hh"

/**
 * Calculate a fibnacci number
 *
 * Precondition: None
 * Postcondition: The fibonacci number is returned
 *
 * @param unsigned int num The fibonacci number to calculated
 * @return unsigned int the calculated fibonacci number
 */
unsigned int fib(unsigned int num)
{
    if (num == 0)
    {
        return 0;
    }
    else if (num == 1)
    {
        return 1;
    }
    else
    {
        return fib(num - 1) + fib(num - 2);
    }
}