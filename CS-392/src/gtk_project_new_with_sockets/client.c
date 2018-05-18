#define CLIENT_INC
#include "socketsgtk.h"

/*
 * client.c
 *
 * The client portion of the server
 * Call with './client server portNum'
 *
 * Valid commands:
 *     /me
 *    /nick
 *    /exit
 *
 * Precondition: Server is running, and correct information is used when
 *        starting the client
 * Postcondition: Client is running
 *
 * @param argc - The number of command line arguments
 * @param argv - The vector of command line arguments
 */
int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);

    gl_env.sockfd = -1;
    
    render_main_window();

    return 0;
}