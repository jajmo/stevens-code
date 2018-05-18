#include "sockets.h"

/*
 * disconnect()
 *
 * SIGINT handler for the client
 *
 * Precondition: None
 * Postcondition: /exit is sent to the server, and the client shuts down
 */
extern int sockfd;

void disconnect()
{
    write(sockfd, "/exit", 6);
    my_str("Bye!\n");
    exit(0);
}