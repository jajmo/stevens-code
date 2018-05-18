#include "my.h"

/*
 * my_strfind()
 *
 * Returns a pointer to needle in str
 *
 * Precondition: str is not null, and needle is not \0
 * Postcondition: A pointer to needle in str is returned, or NULL if not found
 *
 * @param str - The search string
 * @param needle - The character to search for
 * @return char* - A pointer to needle in str
 */
char* my_strfind(char* str, char needle)
{
    if(str != NULL && needle != '\0')
    {
        for( ; *str; str++)
        {
            if(*str == needle)
                return str;
        }
    }

    return NULL;
}
