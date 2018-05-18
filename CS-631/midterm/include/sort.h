#ifndef _SORT_H_
#define _SORT_H_

#include <sys/stat.h>
#include <sys/types.h>

#include <fts.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "config.h"

int fts_cmp(const FTSENT**, const FTSENT**);

#endif /* !_SORT_H_ */