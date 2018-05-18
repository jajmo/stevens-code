#include "my.h"

/*
 * my_strncpy()
 *
 * Copy the first num characters of src into dst
 *
 * Precondition: num is less than or equal to the length of src, and dst is not
 * null
 * Postcondition: A pointer to dst is returned
 *
 * @param dst - The destination memory address
 * @param src - The source string to copy
 * @param num - The number of characters to copy from src
 * @return char* - A pointer to dst
 */
char* my_strncpy(char* dst, char* src, unsigned int num)
{
    unsigned int counter;

    if(dst != NULL && src != NULL && num > 0)
    {
        counter = 0;

        for( ; src[counter] && counter < num; counter++)
            dst[counter] = src[counter];

        if(num > my_strlen(src))
            dst[counter] = '\0';
    }

    return dst;
}
