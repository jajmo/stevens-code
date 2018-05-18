#include "myselect.h"

/*
 * term_standout()
 *
 * Turn on highlighting
 *
 * Precondition: Termcaps have been initialized
 * Postcondition: Highlighting is turned on
 */
void term_standout()
{
    tputs(gl_env.standout, 1, my_termprint);
}