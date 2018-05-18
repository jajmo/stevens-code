#include "my.h"

/*
 * my_num_base()
 *
 * Prints a number to stdout in an alternate base
 *
 * Precondition: number is a valid integer, and symbols is a valid char*
 * Postcondition: number using symbols's symbols is printed
 *
 * @param number - The number to convert
 * @param symbols - A char* representation of the base to be used
 */
void my_num_base(int number, char* symbols)
{
    int base = my_strlen(symbols);
    unsigned int counter;
    unsigned int newNumber;
    unsigned int power = 1;

    if(base > 0 && symbols != NULL)
    {
        if(number < 0)
        {
            my_char('-');
            newNumber = number * -1;
        }
        else
        {
            newNumber = number;
        }

        if(base == 1)
        {
            //Special case
            for(counter = 0; counter < newNumber; counter++)
                my_char(symbols[0]);
        }
        else
        {
            while(power <= (newNumber / base))
                power *= base;
            
            do
            {
                my_char(symbols[newNumber / power]);
                newNumber %= power;
                power /= base;
            } while(power);
        }
    }
    else
    {
        my_str("Base not valid");
    }
}
