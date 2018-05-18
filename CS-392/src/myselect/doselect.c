#include "myselect.h"

/*
 * doselect()
 *
 * Select or deselect an element
 *
 * Precondition: None
 * Postcondition: The item is either highlighted or unhighlighted
 */
void doselect()
{
    gl_env.elements[gl_env.pos].mode = !gl_env.elements[gl_env.pos].mode;
    if(gl_env.elements[gl_env.pos].mode)
    {
        movedown();
    }
    else
    {
        refreshin();
    }
}