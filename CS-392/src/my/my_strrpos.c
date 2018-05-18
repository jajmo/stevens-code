#include "my.h"

/*
 * my_strrpo()
 *
 * Returns the last occurance of c in text
 *
 * Precondition: text is a valid string
 * Postcondition: The last location of c is returned
 *
 * @param text - The string to be searched
 * @param c - The char to search for
 * @return The last index of c in text, or -1 if not found
 */
int my_strrpos(char* text, char c)
{
    unsigned int counter = 0;
    int location = INVALID;

    if(text != NULL)
    {
        while(text[counter])   
        {
            if(text[counter] == c)
                location = counter;

            counter++;
        }
    }

    return location;
}
