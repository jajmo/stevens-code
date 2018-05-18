#include "mynotsominishell.h"

/*
 * move_cursor_to_pos()
 *
 * Move a cursor to a certain position
 *
 * Precondition: None
 * Postcondition: The cursor is moved to pos
 *
 * @param int pos The position to move the cursor to
 */
void move_cursor_to_pos(int pos)
{
    if(gl_env.pos < pos)
    {
        while(gl_env.pos++ < pos)
        {
            tputs(gl_env.move_right, 1, my_termprint);
        }
        gl_env.pos--;
    }
    else
    {
        while(gl_env.pos-- > pos)
        {
            tputs(gl_env.backspace, 1, my_termprint);
        }
        gl_env.pos++;
    }
}