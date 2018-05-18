#include "myselect.h"

/*
 * movedown()
 *
 * Move the cursor down one
 *
 * Precondition: Termcaps are initialized
 * Postcondition: The cursor is moved down one
 */
void movedown()
{
    refreshout(gl_env.pos);
    if(++gl_env.pos > gl_env.nbelems - 1)
    {
        gl_env.pos = 0;
    }
    refreshin();
}