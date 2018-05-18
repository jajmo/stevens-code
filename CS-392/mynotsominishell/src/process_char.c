#include "mynotsominishell.h"

/*
 * process_char()
 *
 * Process a single character, redrawing lines if inserting into the middle and adding to history
 *
 * Preocondition: History is initialized
 * Postcondition: c is printed and added to the history
 *
 * @param char c The character to process
 */
void     process_char(char c)
{
    int  i;
    char swp;

    if(gl_env.pos == gl_env.count)
    {
        gl_env.history[gl_env.current_history][gl_env.count++] = c;
        gl_env.pos++;
        my_char(c);
    }
    else
    {
        gl_env.history[gl_env.current_history][++gl_env.count] = ' ';

        for(i = gl_env.count; i > gl_env.pos; i--)
        {
            swp = gl_env.history[gl_env.current_history][i];
            gl_env.history[gl_env.current_history][i] = gl_env.history[gl_env.current_history][i - 1];
            gl_env.history[gl_env.current_history][i - 1] = swp;
        }

        rewrite_pos_to_end(gl_env.pos, gl_env.current_history);
        my_char(c);
        gl_env.history[gl_env.current_history][gl_env.pos++] = c;
    }
}