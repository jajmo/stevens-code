#ifndef _PRINT_H_
#define _PRINT_H_

#include <sys/param.h>
#include <sys/stat.h>
#if defined(__linux__)
#include <sys/sysmacros.h>
#endif
#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <fts.h>
#include <grp.h>
#include <libgen.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "helpers.h"
#include "sort.h"

void fts_traverse(char**, int);
void fts_print(FTSENT*);
void print_perms(mode_t);
char *get_blocks(unsigned int);
char *get_user(uid_t);
char *get_group(gid_t);
void print_last_modified(time_t);
void long_print(FTSENT*);
void short_print(FTSENT*);
char *get_symbol(mode_t);
void update_columns(FTSENT*);
char *get_human_size(off_t);
char *get_minor(dev_t);
char *get_major(dev_t);

#endif /* !_PRINT_H_ */