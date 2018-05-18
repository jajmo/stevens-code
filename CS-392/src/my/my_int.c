#include "my.h"

/*
 * my_int()
 *
 * Prints an integer to stdout
 *
 * Precondition: num is a valid integer
 * Postcondition: num is printed to the screen
 *
 * @param num - The integer to be printed
 */
void my_int(int num)
{
    unsigned int power = 1;
    unsigned int newNum;

    if(num < 0)
    {
        my_char('-');
        newNum = num * -1;
    }
    else
    {
        newNum = num;
    }
    
    while(power <= (newNum / 10))
        power *= 10;

    do
    {
        my_char('0' + (newNum / power));
        newNum %= power;
        power /= 10;
    } while(power);
}
