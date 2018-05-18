#include "myselect.h"

/*
 * term_move_to_item()
 *
 * Move the cursor to an item
 *
 * Precondition: pos is a valid item
 * Postcondition: The cursor is moved to item at pos
 *
 * @param int pos - The array index of the item to move to
 */
void term_move_to_item(int pos)
{
    tputs(tgoto(gl_env.move, gl_env.elements[pos].x, gl_env.elements[pos].y), 1, my_termprint);
}