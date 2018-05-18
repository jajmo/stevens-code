#include "sockets.h"

extern struct s_gl_env gl_env;

/*
 * serv_kill()
 *
 * The SIGINT handler of the child processes of server
 *
 * Precondition: None
 * Postcondition: The child process is stopped
 */
void serv_kill()
{
    usleep(getpid());
    free(gl_env.username);
    close(gl_env.sockfd);
    exit(0);
}