#include "sockets.h"

/*
 * bye()
 *
 * Callback for SIGINT for the main process of server
 *
 * Precondition: None
 * Postcondition: The server shuts down
 */
void bye()
{
    usleep(2 * getpid());
    my_str("\nServer shutting down...Goodbye!\n");
    exit(0);
}