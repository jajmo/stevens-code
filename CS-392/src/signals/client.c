#define CLIENT_INC
#include "mysignals.h"

/*
 * The client portion of the server.
 * Sends a message to the server via signals.
 *
 * The command line arguments are as followed:
 * ./client [PID of the server] [String to send]
 *
 * If the server does not acknowledge the client, it raises a SIGALRM.
 *
 * Last Edit: 10/21/14 12:00 PM
 */
int       gl_ack;

int       main(int argc, char** argv)
{
    pid_t serverpid;

    gl_ack = 0;

    if(argc < 3)
    {
        my_str("Usage: ./client serverpid arg1 [arg2] ...\n");
        exit(0);
    }

    if((serverpid = my_atoi(argv[1])) <= 0)
    {
        my_str("Invalid server PID!\n");
        exit(0);
    }

    signal(SIGUSR1, ack);
    signal(SIGUSR2, nothing);
    signal(SIGALRM, myalarm);

    sendpid(getpid(), serverpid);

    if(!gl_ack)
    {
        alarm(2);
        pause();
    }
    alarm(0);

    sendmessage(my_vect2str(&argv[2]), serverpid);

    return 0;
}

void nothing()
{
}

void ack()
{
    gl_ack = 1;
}

void myalarm()
{
    my_str("Connection timed out! Shutting down...\n");
    exit(0);
}
