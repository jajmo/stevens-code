#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "common.h"

int error_response(char *, char *, int);
char *construct_response_text(char *, char *);
char *get_server_headers(const char *, int);

#endif