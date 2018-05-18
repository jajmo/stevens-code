#include "my.h"

/*
 * my_strpos()
 *
 * Returns the first occurence of c in String
 *
 * Precondition: char* is a valid string
 * Postcondition: The first index of c inside String
 *
 * @param String - The string to search in
 * @param c - The char being searched for
 * @return The index of the first occurance of c, or -1 if not found
 */
int my_strpos(char* String, char c)
{
    unsigned int counter = 0;

    if(String != NULL)
    {
        while(String[counter])
        {
            if(String[counter] == c)
                return counter;

            counter++;
        }
    }

    return INVALID;
}
