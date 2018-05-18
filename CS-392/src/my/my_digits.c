#include "my.h"

/*
 * my_digits()
 *
 * Precondition: None
 * Postcondition: Digits 0-9 are printed on the screen
 *
 * Prints all the digits from 0-9, without using any data type larger
 * than 1 byte
 */
void my_digits()
{
    char start;

    for(start = '0'; start <= '9'; start++)
        my_char(start);
}
