#include "myselect.h"

/*
 * moveleft()
 *
 * Move the cursor left
 *
 * Precondition: Termcaps are intialized
 * Postcondition: The cursor is moved one spot to the left
 */
void moveleft()
{
    refreshout(gl_env.pos);
    gl_env.pos -= gl_env.win.ws_row ;
    if(gl_env.pos < 0)
    {
        gl_env.pos = 0;
    }
    refreshin();
}