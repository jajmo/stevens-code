#include "myselect.h"

/*
 * term_clear()
 *
 * Clear the terminal
 *
 * Precondition: None
 * Postcondition: The terminal is cleared
 */
void term_clear()
{
    tputs(gl_env.clear, 1, my_termprint);
}