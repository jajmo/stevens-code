#ifndef _SWS_H_
#define _SWS_H_

#if defined(__linux__)
#include <bsd/bsd.h>
#endif

#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>

#include "common.h"
#include "config.h"
#include "net.h"

void handle_signal(int);

#endif