# Makefile for tcp/tcpm

TCPNAME=tcp
TCPSRC=tcp.c

TCPMNAME=tcpm
TCPMSRC=tcpm.c

TCPOBJ=$(TCPSRC:.c=.o)
TCPMOBJ=$(TCPMSRC:.c=.o)

RM=rm -f
CFLAGS+= -Wall -Werror

all: tcp tcpm

tcp:$(TCPOBJ)

tcpm:$(TCPMOBJ)

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core
	-$(RM) existing
	-$(RM) small

fclean: clean
	-$(RM) $(TCPMNAME)
	-$(RM) $(TCPNAME)

re: fclean all
