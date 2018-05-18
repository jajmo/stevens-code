#include "mynotsominishell.h"

/*
 * history_down()
 *
 * Move down one spot in history
 *
 * Precondition: History is initialized
 * Postcondition: History is moved down one index and printed
 */
void history_down()
{
    clear_input();
    gl_env.count = my_strlen(gl_env.history[++gl_env.current_history]);
    gl_env.pos = 0;
    rewrite_pos_to_end(0, gl_env.current_history);
    move_cursor_to_pos(gl_env.count);
}