#include "myselect.h"

/*
 * init_caps()
 *
 * Get and initialize all of the termcaps
 *
 * Precondition: None
 * Postcondition: All of the caps in gl_env are set
 */
void      init_caps()
{
    char* term;
    char  bp[2048];

    term = getenv("TERM");
    tgetent(bp, term);

    gl_env.left = term_get_cap(LEFT);
    gl_env.right = term_get_cap(RIGHT);
    gl_env.up = term_get_cap(UP);
    gl_env.down = term_get_cap(DOWN);
    gl_env.underline = term_get_cap(UNDERLINE);
    gl_env.under_end = term_get_cap(UNDER_END);
    gl_env.standout = term_get_cap(STANDOUT);
    gl_env.stand_end = term_get_cap(STAND_END);
    gl_env.move = term_get_cap(MOVE);
    gl_env.clear = term_get_cap(CLEAR);
    gl_env.cursoroff = term_get_cap(CURSOROFF);
    gl_env.cursoron = term_get_cap(CURSORON);
}