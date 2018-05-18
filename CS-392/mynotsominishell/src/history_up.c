#include "mynotsominishell.h"

/*
 * history_up()
 *
 * Move up one spot in history
 *
 * Precondition: History is initialized
 * Postcondition: The history one index up is printed
 */
void history_up()
{
    clear_input();
    gl_env.count = my_strlen(gl_env.history[--gl_env.current_history]);
    gl_env.pos = 0;
    rewrite_pos_to_end(0, gl_env.current_history);
    move_cursor_to_pos(gl_env.count);
}