/*
 * sockets.h
 *
 * Communication between a server and several clients
 * using sockets
 *
 * Last Modified: 10/30/14 11:47 PM
 */

#ifndef _SOCKETS_H_
#define _SOCKETS_H_
#define BUFFER_SIZE 512

#include "my.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

int sockfd;

struct s_gl_env
{
	int sockfd;
	char* username;
	int pid;
} gl_env;

#ifdef SERVER_INC
 	void bye();
 	void serv_kill();
#else
#include <netdb.h>
 	void disconnect();
#endif
#endif
