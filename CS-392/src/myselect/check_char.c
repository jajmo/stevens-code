#include "myselect.h"

/*
 * check_char()
 *
 * Handle processing of the input
 *
 * Precondition: Parameter is not void
 * Postcondition: The input is processed
 *
 * @param char* input The input
 */
void    check_char(char* input)
{
    int count;

    if(input != NULL)
    {
        if(!my_strcmp(input, KU))
        {
            moveup();
        }
        else if(!my_strcmp(input, KD))
        {
            movedown();
        }
        else if(!my_strcmp(input, KL))
        {
            moveleft();
        }
        else if(!my_strcmp(input, KR))
        {
            moveright();
        }
        else if(!my_strcmp(input, " "))
        {
            doselect();
        }
        else
        {
            getout(input);
        }
    }
}