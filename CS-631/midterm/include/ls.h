#ifndef _LS_H_
#define _LS_H_

#include <sys/ioctl.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "print.h"

int main(int, char **);
static void usage();

#endif /* !_LS_H_ */