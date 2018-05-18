#include "my.h"

/*
 * my_strconcat()
 *
 * Concatinates str1 and str2 together
 *
 * Precondition: Neither parameters are null
 * Postcondition: A new string is returned
 *
 * @param str1 - The first string to concatinate
 * @param str2 - The second string to concatinate
 * @return char* - The new string
 */
char* my_strconcat(char* str1, char* str2)
{
    char* newString;
    unsigned int totalLength;

    if(str1 == NULL && str2 == NULL)
        return NULL;

    if(str1 == NULL) 
        return my_strdup(str2);
    else if(str2 == NULL)
        return my_strdup(str1);

    totalLength = my_strlen(str1) + my_strlen(str2) + 1;
    newString = (char*) xmalloc(totalLength * sizeof(char));

    my_strcpy(newString, str1);
    my_strcat(newString, str2);

    return newString;
}
