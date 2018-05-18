#include "mynotsominishell.h"

/*
 * shift_history()
 *
 * Move the history up by 1
 *
 * Precondition: History is initialized
 * Postcondition: The history is shifted up by 1 spot
 */
void      shift_history()
{
    char* swp;
    int   i;

    for(i = 0; i < HISTORY_SIZE - 1; i++)
    {
        swp = gl_env.history[i];
        gl_env.history[i] = gl_env.history[i + 1];
        gl_env.history[i + 1] = swp;
    }

    gl_env.history[HISTORY_SIZE - 1][0] = '\0';
}