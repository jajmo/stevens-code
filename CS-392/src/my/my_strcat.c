#include "my.h"

/*
 * my_strcat()
 *
 * Puts str2 at the end of str1
 *
 * Precondition: str1 is not null, and has enough free space for str2
 * Postcondition: str1 has str2 concatinated at the end
 *
 * @param str1 - The destination string
 * @param str2 - The source string
 * @return char* - A pointer to the beginning of str1
 */
char* my_strcat(char* str1, char* str2)
{
    char* str1start;

    if(str1 != NULL && str2 != NULL)
    {
       str1start = str1;
       str1 += my_strlen(str1);

       for( ; *str2; str2++, str1++)
            *str1 = *str2;

       *str1 = '\0';
       str1 = str1start;
    }

    return str1;
}
