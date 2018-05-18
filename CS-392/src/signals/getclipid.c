#include "mysignals.h"

/*
 * getclipid()
 *
 * Callback for SIGUSR1 and SIGUSR2 in server.c
 * Convert the bits recieved from the client into a number
 *
 * Precondition: None
 * Postcondition: The client pid is updated with either a 0 or 1, depending
 * on the signal recieved
 *
 * @param sig - The signal recieved
 */
void getclipid(int sig)
{
    gl_env.clipid <<= 1;

    if(sig == SIGUSR1)
    {
        gl_env.clipid |= 1;
    }
}
