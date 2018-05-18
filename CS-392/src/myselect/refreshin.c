#include "myselect.h"

/*
 * refreshin()
 *
 * Reshow an item with underline
 *
 * Precondition: Termcaps are initialized
 * Postcondition: The item is shown with an underline
 */
void refreshin()
{
    term_move_to_item(gl_env.pos);
    term_underline();
    if(gl_env.elements[gl_env.pos].mode)
    {
        term_standout();
    }
    my_str(gl_env.elements[gl_env.pos].elem);
    term_standend();
    term_underend();
}