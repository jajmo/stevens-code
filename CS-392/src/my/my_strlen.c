#include "my.h"

/*
 * my_strlen()
 *
 * Returns the length of a string
 *
 * Precondition: string is a valid string
 * Postcondition: The string length is returned, or -1 if the string is null
 *
 * @param string - The string to find the length of
 * @return The length of string
 */
int my_strlen(char* string)
{
    int stringLength = INVALID;

    if(string != NULL)
    {
        stringLength = 0;

        while(string[stringLength])
            stringLength++;
    }

    return stringLength;
}
