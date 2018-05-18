#include "my.h"

/*
 * my_strrfind()
 *
 * Finds the last occurence of needle in str, and returns a pointer to that
 * location
 *
 * Precondition: str is not null, and needle is not \0
 * Postcondition: A pointer to the last occurence of needle in str is returned,
 * or null if not found
 *
 * @param str - The search string
 * @param needle - The character to search for
 * @retnr char* - A pointer to the last occurence of needle in str, or null if
 * not found
 */
char* my_strrfind(char* str, char needle)
{
    char* lastLocation = NULL;

    if(str != NULL && needle != '\0')
    {

        for( ; *str; str++)
        {
            if(*str == needle)
                lastLocation = str;
        }

        if(lastLocation != NULL)
        {
            str = lastLocation;
            return str;
        }
    }

    return NULL;
}
