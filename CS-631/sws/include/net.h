#ifndef _NET_H_
#define _NET_H_

#if defined(__linux__)
#define _GNU_SOURCE
#endif

#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "common.h"
#include "config.h"
#include "fs.h"
#include "parse.h"
#include "response.h"
#include "cgi_handler.h"

/* Socket timeout, in seconds */
#define SOCKET_TIMEOUT 60

typedef enum { Cgi_Request,Static_Request,Other_Request } _request_type;

void handle_client(int);
int setup_socket();
int handle_code(int *, int);

#endif
