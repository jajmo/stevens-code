#include "myselect.h"

/*
 * moveright()
 *
 * Move the cursor one spot to the right
 *
 * Precondition: Termcaps are initialized
 * Postcondition: The cursor is moved one spot to the right
 */
void moveright()
{
    refreshout(gl_env.pos);
    gl_env.pos += gl_env.win.ws_row;
    if(gl_env.pos >= gl_env.nbelems)
    {
        gl_env.pos = gl_env.nbelems - 1;
    }
    refreshin();
}