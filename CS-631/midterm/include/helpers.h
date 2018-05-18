#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <fts.h>
#include <libgen.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

void *xmalloc(size_t);
int num_len(unsigned long);
BOOL need_show_file(FTSENT *);
char *sanitize(char *);
void reset_sizes();

#endif /* !_HELPERS_H_ */