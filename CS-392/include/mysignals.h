#ifndef _MYSIGNALS_H_
#define _MYSIGNALS_H_

#include "my.h"
#include <signal.h>

extern struct s_gl_env
{
	int clipid;
	char done;
} gl_env;

extern int gl_ack;

#ifdef SERVER_INC

void handler();
void getclipid(int);
void getmessage(int);

#else

void ack();
void myalarm();
void nothing();
void sendmessage(char*, pid_t);
void sendpid(pid_t, pid_t);

#endif
#endif