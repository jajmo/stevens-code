#include "my.h"

/*
 * my_strdup()
 *
 * Duplicates text into the heap
 *
 * Precondition: text is not null
 * Postcondition: A pointer to the new string is returned
 *
 * @param text - The string to be duplicated
 * @return char* - A pointer to the new string, or NULL
 */
char* my_strdup(char* text)
{
    char* newStr = NULL;
    int strlen = my_strlen(text);

    if(strlen  > -1)
    {
        newStr = (char*) xmalloc(strlen * sizeof(char) + 1);

        for( ; *text; newStr++, text++)
            *newStr = *text;

        *newStr = '\0';
        newStr -= strlen;
    }

    return newStr;
}
