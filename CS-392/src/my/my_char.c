#include "my.h"

/*
 * my_char()
 *
 * Writes one byte into the standard output
 *
 * Precondition: Takes a char
 * Postcondition: Prints the char to stdout
 *
 * @param c - The byte to be printed
 */
void my_char (char c) 
{
    write(1, &c, 1);
}
