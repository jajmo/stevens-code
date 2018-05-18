#include "myselect.h"

/*
 * refreshout()
 *
 * Reshow an item without underline
 *
 * Precondition: int is on the screen
 * Postcondition: The item at pos is printed
 *
 * @param int pos - The position in the array of the item to print
 */
void refreshout(int pos)
{
    term_move_to_item(pos);
    if(gl_env.elements[pos].mode)
    {
        term_standout();
    }
    my_str(gl_env.elements[pos].elem);
    term_standend();
}