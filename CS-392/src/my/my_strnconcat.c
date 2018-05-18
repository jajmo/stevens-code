#include "my.h"

/*
 * my_strnconcat()
 *
 * Concatinate the first num characters of str2 to str1
 *
 * Precondition: num is less than or equal to the length of str2
 * Postcondition: A new string is returned containing all of str1
 * and the first num characters of str2
 *
 * @param str1 - The first string
 * @param str2 - The string to concatinate
 * @param num - The number of characters from str2 to concatinate
 * @return char* - A new string containing str1 and the first num characters of
 * str2
 */
char* my_strnconcat(char* str1, char* str2, unsigned int num)
{
    char* returnString;
    unsigned int totalSize;
    unsigned int counter;
    unsigned int strPos;

    if(str2 == NULL && str1 == NULL)
        return NULL;

    if(num == 0 || str2 == NULL)
        return my_strdup(str1);

    if(num > my_strlen(str2))
        return my_strconcat(str1, str2);

    totalSize = (my_strlen(str1) > 0) ? my_strlen(str1) + num + 1 : num + 1;
    returnString = (char*) xmalloc(totalSize * sizeof(char));
    counter = totalSize - num - 1;
    strPos = 0;
    
    my_strcat(returnString, str1);

    for( ; str2[strPos] && strPos < num; strPos++, counter++)
        returnString[counter] = str2[strPos];

    returnString[counter] = '\0';

    return returnString;
}
