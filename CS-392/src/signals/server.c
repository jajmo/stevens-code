#define SERVER_INC
#include "mysignals.h"

/*
 * The server portion of the project.
 * It handles the recieving of the client PID, and the string from the client.
 *
 * Usage: ./server
 * It takes no arguments
 *
 * Last Edit: 10/21/14 11:59 AM
 */
struct  s_gl_env gl_env;

int     main()
{
    int count;

    signal(SIGINT, handler);

    my_str("Server PID: ");
    my_int(getpid());
    my_str("\n\n");

    while(1)
    {
        gl_env.clipid = 0;
        gl_env.done   = 0;

        signal(SIGUSR1, getclipid);
        signal(SIGUSR2, getclipid);

        for(count = 0; count < (8 * sizeof(pid_t)); count++)
        {
            pause();
        }

        signal(SIGUSR1, getmessage);
        signal(SIGUSR2, getmessage);

        kill(gl_env.clipid, SIGUSR1);

        while(!gl_env.done)
        {
            pause();
        }
        my_str("\n\n");
    }

    return 0;
}
