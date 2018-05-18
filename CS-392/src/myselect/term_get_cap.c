#include "myselect.h"

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
        if(!my_strcmp(cap, CURSOROFF) || !my_strcmp(cap, CURSORON))
        {
            if(!my_strcmp(cap, CURSOROFF))
            {
                ret = VICAP;
            }
            else
            {
                ret = VECAP;
            }
        }
        else
        {
            my_str("Cap ");
            my_str(cap);
            my_str(" not found!\n");
            restore_terminal();
            exit(1);
        }
    }

    return ret;
}