#include "mynotsominishell.h"

/*
 * my_termprint()
 *
 * Write a character to the terminal
 *
 * Precondition: None
 * Postcondition: c is written to the terminal
 *
 * @param int c - The char to write
 * @return int - 0
 */
int my_termprint(int c)
{
    return write(1, &c, 1);
}