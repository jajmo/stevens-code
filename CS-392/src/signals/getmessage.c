#include "mysignals.h"

/*
 * getmessage()
 *
 * Callback for SIGUSR1 and SIGUSR2 in server.c
 * Convert the recieved bits to a string, printed out char by char
 *
 * Precondition: None
 * Postcondition: A char is printed every 8 bits recieved
 *
 * @param sig - The signal recieved to determine if it's a 1 or 0
 */
void getmessage(int sig)
{
    static char current = 0;
    static int counter = 0;

    current <<= 1;

    if(sig == SIGUSR1)
    {
        current |= 1;
    }

    if(++counter >= 8)
    {
        if(current == '\0')
        {
            gl_env.done = 1;
            kill(gl_env.clipid, SIGUSR1);
        }
        else
        {
            my_char(current);
        }
        current = 0;
        counter = 0;
    }

    kill(gl_env.clipid, SIGUSR2);
}