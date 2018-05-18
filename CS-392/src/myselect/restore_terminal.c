#include "myselect.h"

/*
 * restore_terminal()
 *
 * Restore the terminal to its original state
 *
 * Precondition: Terminal is modified for myselect use
 * Postcondition: Terminal is restored to its original state
 */
void restore_terminal()
{
    tputs(gl_env.cursoron, 0, my_termprint);
    term_clear();
    ioctl(0, TCSETA, &(gl_env.line_backup));
    dup2(gl_env.stdio_backup, 1);
}