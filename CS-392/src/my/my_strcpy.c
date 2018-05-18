#include "my.h"

/*
 * my_strcpy()
 *
 * Copies src into dst, overwriting dst
 *
 * Precondition: dst has enough space allocated for src
 * Postcondition: A pointer to dst is returned
 *
 * @param dst - The destination memory address
 * @param src - The string to be copied in
 * @return char* - A pointer to dst, or NULL
 */
char* my_strcpy(char* dst, char* src)
{
    char* dstStart;

    if(dst != NULL && src != NULL)
    {
        dstStart = dst;

        for( ; *src; src++, dst++)
            *dst = *src;

        *dst = '\0';
        dst = dstStart;
    }

    return dst;
}
