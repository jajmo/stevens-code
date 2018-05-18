#include "myselect.h"

/*
 * term_underend()
 *
 * Turn off underline
 *
 * Precondition: Termcaps are initialized
 * Postcondition: Underline is turned off
 */
void term_underend()
{
    tputs(gl_env.under_end, 1, my_termprint);
}