#ifndef _GREET_H_
#define _GREET_H_

#include <stdio.h>
#include <stdlib.h>

void greet(void);
void hello(const char *, const char *);
const char *getgreeting(void);
int setgreeting(const char *);

#endif