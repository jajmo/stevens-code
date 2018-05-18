#ifndef _COMMON_H_
#define _COMMON_H_

#if defined(__linux__)
#include <bsd/bsd.h>
#endif

#include <errno.h>
#include <err.h>
#include <magic.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#include <sys/stat.h>

#include "config.h"

#define SERVER_NAME "sws/1.0"
#define PID_FILE "/var/run/sws.pid"
#define DEFAULT_CONTENT_TYPE "text/html"
#define LOG_FORMAT "%s %s \"%s\" %d %d\n"

#define NOT_MODIFIED_CODE 304
#define NOT_MODIFIED_STATUS "HTTP/1.0 304 Not Modified"

#define BAD_REQUEST_CODE 400
#define BAD_REQUEST_BODY "<html><body><h1>400 Bad Request</h1></body></html>"
#define BAD_REQUEST_STATUS "HTTP/1.0 400 Bad Request"

#define FORBIDDEN_CODE 403
#define FORBIDDEN_BODY "<html><body><h1>403 Forbidden</h1></body></html>"
#define FORBIDDEN_STATUS "HTTP/1.0 403 Forbidden"

#define NOT_FOUND_CODE 404
#define NOT_FOUND_BODY "<html><body><h1>404 Not Found</h1></body></html>"
#define NOT_FOUND_STATUS "HTTP/1.0 404 Not Found"

#define NOT_ALLOWED_CODE 405
#define NOT_ALLOWED_BODY "<html><body><h1>405 Method Not Allowed</h1></body></html>"
#define NOT_ALLOWED_STATUS "HTTP/1.0 405 Method Not Allowed"

#define URI_TOO_LONG_CODE 414
#define URI_TOO_LONG_BODY "<html><body><h1>414 URI Too Long</h1></body></html>"
#define URI_TOO_LONG_STATUS "HTTP/1.0 414 URI Too Long"

#define SERVER_ERROR_CODE 500
#define SERVER_ERROR_BODY "<html><body><h1>500 Internal Server Error</h1></body></html>"
#define SERVER_ERROR_STATUS "HTTP/1.0 500 Internal Server Error"

#define NOT_IMPLEMENTED_CODE 501
#define NOT_IMPLEMENTED_BODY "<html><body><h1>501 Not Implemented</h1></body></html>"
#define NOT_IMPLEMENTED_STATUS "HTTP/1.0 501 Not Implemented"

#define VERSION_NOT_SUPPORTED_CODE 505
#define VERSION_NOT_SUPPORTED_BODY "<html><body><h1>505 HTTP Version Not Supported</h1></body></html>"
#define VERSION_NOT_SUPPORTED_STATUS "HTTP/1.0 505 Version Not Supported"

#define SUCCESS_CODE 200
#define SUCCESS_STATUS "HTTP/1.0 200 OK"

#define MODIFIED_SINCE_HEADER_NAME "If-Modified-Since:"

void cleanup();
void usage();
void warn_and_die(int, char *, ...);
void log_request(int, int);
const char *get_magic_buffer(char *);
const char *get_magic_file(char *);
magic_t get_magic_cookie();
int elem_count(char *);
int is_valid_path(const char *path);
char *get_cgi_absolute_path(const char *path);
int validate_stat(const char *path,struct stat *req_stat);
void cgi_response(char *buffer, int buflen,int cli_sock);

#endif