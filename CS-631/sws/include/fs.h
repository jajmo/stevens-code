#ifndef _FS_H_
#define _FS_H_

#include <dirent.h>
#include <limits.h>
#include <stdlib.h>

#include <sys/stat.h>

#include "common.h"
#include "parse.h"
#include "response.h"

int generate_directory_listing(char *, int, int *);
void get_html_listing(char *, char *, char *, struct dirent *);
int send_file_response(char *, int, int *, time_t);

#endif