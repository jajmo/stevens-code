#include "main.hh"

/**
 * Get the index of a value in main memory
 *
 * Precondition: None
 * Postcondition: The index is returned
 *
 * @param int val The value to search for
 * @return int The index or -1
 */
int getIndex(int val)
{
    int size;
    int idx;
    int count;

    idx = -1;
    size = gl_env.mainMemory.size();
    for (count = 0; count < size; count++)
    {
        if (gl_env.mainMemory.at(count) == val)
        {
            idx = count;
            break;
        }
    }

    return idx;
}