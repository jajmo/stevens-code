#include "my.h"

/*
 * xmalloc()
 *
 * A wrapper function for malloc()
 *
 * Precondition: None
 * Postcondition: The memory block is created
 *
 * @param n - The number of bytes needed
 * @return void* - A pointer to the allocated memory
 */
void* xmalloc(unsigned int n)
{
    void* p;

    if((p = malloc(n)) == NULL)
    {
        my_str("Virtual memory exhausted\n");
        exit(1);
    }

    return p;
}
