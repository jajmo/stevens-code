#include "myselect.h"

/*
 * term_standend()
 *
 * Turn off highlighting
 *
 * Precondition: Termcaps are initialized
 * Postcondition: Highlighting is turned off
 */
void term_standend()
{
    tputs(gl_env.stand_end, 1, my_termprint);
}