#ifndef _PARSE_H_
#define _PARSE_H_

/* Needed for strptime(3) on linux */
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "common.h"

#define BAD_REQUEST -1
#define NOT_ALLOWED -2

#define VALID_URI_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789:/?#[]@!$&'()*+,;=-._~%"

void urlencode(char *, char *);
char *urldecode(char *);
char *parse_uri(char *);
int validate_uri(char *);
int parse_method(char *);
int parse_version(char *);
time_t parse_modified_since(char *);
int parse_request(char *, int);

#endif
