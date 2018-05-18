#include "my.h"

/*
 * my_str()
 *
 * Print a string to stdout
 *
 * Precondition: String is a valid char*
 * Postcondition: String is printed to the screen
 *
 * @param String - The string to be printed
 */
void my_str(char* String)
{
    unsigned int counter;

    if(String != NULL)
    {
        counter = 0;

        while(String[counter])
        {
            my_char(String[counter]);
            counter++;
        }
    }
}
