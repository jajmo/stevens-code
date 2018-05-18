#include "mysignals.h"

/*
 * sendpid()
 *
 * Send the running process ID to a server
 *
 * Precondition: serverpid is a valid running process
 * Postcondition: clipid is sent to the server
 *
 * @param clipid - The PID to send to the server
 * @param serverpid - The PID to send clipid to
 */
void    sendpid(pid_t clipid, pid_t serverpid)
{
    int mask;
    int count;

    mask = 1 << (8 * sizeof(pid_t) - 1);
    for(count = 0; count < (8 * sizeof(pid_t)); count++, clipid <<= 1)
    {
        if(clipid & mask)
        {
            kill(serverpid, SIGUSR1);
        }
        else
        {
            kill(serverpid, SIGUSR2);
        }
        usleep(2000);
    }

}
