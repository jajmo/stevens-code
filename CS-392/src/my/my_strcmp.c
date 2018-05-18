#include "my.h"

/*
 * my_strcmp()
 *
 * Compares str1 to str2
 *
 * Precondition: None
 * Postcondition: The comparison of str1 to str2 is returned
 *
 * @param str1 - The first string to compare
 * @param str2 - The second string to compare
 * @return int - Positive if s1 > s2
 *               Negative if s1 < s2
 *               Zero if the strings are equal
 */
int my_strcmp(char* str1, char* str2)
{
    if(str1 == NULL && str2 == NULL)
        return 0;

    if(str1 == NULL)
        return -1;
    else if(str2 == NULL)
        return 1;

    for( ; *str1 && *str2 && (*str1 == *str2); str1++, str2++);

    return *str1 - *str2;
}
