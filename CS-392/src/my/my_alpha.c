#include "my.h"

/*
 * my_alpha()
 *
 * Precondition: None
 * Postcondition: a-z is printed on the screen
 *
 * Prints the letters of the alphabet from a-z without using any data type
 * larger than 1 byte
 */
void my_alpha()
{
    char count;

    for(count = 'a'; count <= 'z'; count++)
        my_char(count);
}
