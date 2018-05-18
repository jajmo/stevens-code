#include "myselect.h"

/*
 * term_underline()
 *
 * Turn on underline
 *
 * Precondition: Termcaps are initialized
 * Postcondition: Underline is turned on
 */
void term_underline()
{
    tputs(gl_env.underline, 1, my_termprint);
}