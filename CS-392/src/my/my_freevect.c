#include "my.h"

/*
 * my_freevect()
 *
 * Free the memory used by a vector
 *
 * Precondition: vect is not null
 * Postcondition: The memory is freed
 *
 * @param vect - The vector to free
 */
void    my_freevect(char** vect)
{
    int count;

    if(vect != NULL)
    {
        for(count = 0; vect[count]; count++)
        {
            free(vect[count]);
        }

        free(vect);
    }
}