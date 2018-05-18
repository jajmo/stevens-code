#include "mysignals.h"

/*
 * sendmessage()
 *
 * Send a message to another running process via signals
 *
 * Precondition: Message is not null, serverpid is a valid running process
 * Postcondition: The message is sent
 *
 * @param message - The message to send
 * @param serverpid - The process ID of the recieving process
 */
void     sendmessage(char* message, pid_t serverpid)
{
    char mask;
    char count;

    if(message != NULL)
    {
        mask = 0x80;
        gl_ack = 0;
        count = 0;
        while(!gl_ack)
        {
            if(*message & mask)
            {
                kill(serverpid, SIGUSR1);
            }
            else
            {
                kill(serverpid, SIGUSR2);
            }

            if(++count == 8)
            {
                message++;
                count = 0;
            }
            else
            {
                *message <<= 1;
            }
            pause();
        }
    }
}
