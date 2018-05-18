#include "mynotsominishell.h"

/*
 * term_get_cap()
 *
 * Get a termcap, return it as a char*
 *
 * Precondition: cap is not null
 * Postcondition: The termcap string is returned
 *
 * @param char* cap - The termcap to get
 * @return char* - The termcap string
 */
char*             term_get_cap(char* cap)
{
    static char area[2048];
    char*       ret;

    if(!(ret = tgetstr(cap, (char**) &area)))
    {
        my_str("Cap ");
        my_str(cap);
        my_str(" not found!\n");
        exit(1);
    }

    return ret;
}