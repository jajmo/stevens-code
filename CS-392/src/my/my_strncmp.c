#include "my.h"

/*
 * my_strncmp()
 *
 * Compare the first num characters of s2 to s1
 *
 * Precondition: num > 0
 * Postcondition: The comparison is returned
 *
 * @param s1 - The first string to compare
 * @param s2 - The second string to compare
 * @param num - The number of characters to compare
 * @return int - A negative number if s1 < s2
 *               A positive number if s1 > s2
 *               Zero if s1 == s2
 */
int my_strncmp(char* s1, char* s2, unsigned int num)
{
    unsigned int counter;

    if((s1 == NULL && s2 == NULL) || (num == 0 && s1 != NULL && s2 != NULL))
        return 0;

    if(s1 == NULL)
        return -1;
    else if(s2 == NULL)
        return 1;

    counter = 0;

    for( ; *s1 && *s2 && (*s1 == *s2) && counter < num - 1; counter++, s1++, s2++);

    return *s1 - *s2;
}
