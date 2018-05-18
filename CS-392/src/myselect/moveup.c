#include "myselect.h"

/*
 * moveup()
 *
 * Move the cursor up one position
 *
 * Precondition: Termcaps are intialized
 * Precondition: The cursor position is set
 */
void moveup()
{
    refreshout(gl_env.pos);
    if(--gl_env.pos < 0)
    {
        gl_env.pos = gl_env.nbelems - 1;
    }
    refreshin();
}