#include "my.h"

/*
 * my_atoi()
 *
 * Convert a string to an integer
 *
 * Precondition: str contains at least one valid number
 * Postcondition: The number in integer form is returned
 *
 * @param str - The string to convert to an int
 * @return int - The int extracted from the string
 */
int my_atoi(char* str)
{
    int sign;
    int res;
    if(str != NULL)
    {
        while(*str == ' ')
        {
            str++;
        }
        sign = 1;
        res = 0;
        for( ; *str && *str != ' ' && (*str == '+' || *str == '-' || (*str <= '9' && *str >= '0')); str++)
        {
            if(*str == '-')
            {
                sign *= -1;
            }
            else if(*str <= '9' && *str >= '0')
            {
                res = (res * 10) + (*str - '0');
            }
        }
        return res * sign;
    }
    return 0;
}
