#include "my.h"

/*
 * my_revstr()
 *
 * Reverses a string
 *
 * Precondition: parameter is a valid string
 * Postcondition: String is reversed and the length is returned
 *
 * @param text - the string to be reversed
 * @return The length of the string
 */
int my_revstr(char* text)
{
    int strlength = my_strlen(text);
    int count; 
    int newCount = strlength - 1;
    char temp;

    if(text != NULL && strlength > 0)
    {
       for(count = 0; count < newCount; count++, newCount--)
       {
           temp = text[count];
           text[count] = text[newCount];
           text[newCount] = temp;
       }
               
    }

    return strlength;
}
