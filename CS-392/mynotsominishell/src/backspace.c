#include "mynotsominishell.h"

/*
 * backspace()
 *
 * Backspace one character
 *
 * Precondition: Termcaps are initialized
 * Postcondition: One character is backspaced
 */
void backspace()
{
    tputs(gl_env.backspace, 1, my_termprint);
    my_char(' ');
    tputs(gl_env.backspace, 1, my_termprint);
    gl_env.history[0][gl_env.count--] = '\0';
    gl_env.pos--;
}