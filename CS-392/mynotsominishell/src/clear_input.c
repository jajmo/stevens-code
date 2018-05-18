#include "mynotsominishell.h"

/*
 * clear_input()
 *
 * Clear the typed input
 *
 * Precondition: None
 * Postcondition: Input is cleared
 */
void    clear_input()
{
    int count_backup;

    count_backup = gl_env.count + 1;

    move_cursor_to_pos(gl_env.count + 1);

    while(count_backup-- > 0)
    {
        tputs(gl_env.backspace, 1, my_termprint);
        my_char(' ');
        tputs(gl_env.backspace, 1, my_termprint);
    }
}