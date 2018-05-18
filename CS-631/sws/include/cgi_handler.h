#ifndef _CGI_HANDLER_H_
#define _CGI_HANDLER_H_

#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#include "net.h"

#define MAX_TIME_SIZE 100

int *handle_cgi(/*Input cgi request*/char *request,int cli_sock);
char *get_cgi_params();

#endif 
