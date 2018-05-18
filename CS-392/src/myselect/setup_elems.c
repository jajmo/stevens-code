#include "myselect.h"

/*
 * setup_elems()
 *
 * Sets up the global elements
 *
 * Precondition: At least 1 element exists
 * Postcondition: The global element information is populated
 *
 * @param int num - The number of elements
 * @param char** elements - The vector of elements
 */
void    setup_elems(int num, char** elements)
{
    int count;

    gl_env.nbelems = num;
    gl_env.elements = xmalloc(num * sizeof(t_elem));

    for(count = 0; count < num; count++)
    {
        gl_env.elements[count].elem = elements[count];
        gl_env.elements[count].size = my_strlen(elements[count]);
        gl_env.elements[count].mode = 0;
    }
}