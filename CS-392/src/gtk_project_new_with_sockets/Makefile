#Makefile for gtksockets

CLINAME=client
CLISRC=client.c disconnect.c render_main_window.c render_connect_window.c \
	   connect_server.c send_message.c render_quit_window.c quit_button.c \
	   close_connect_window.c close_quit_window.c disable_main.c enable_main.c \
	   close_program.c

SERVNAME=server
SERVSRC=server.c

CLIOBJ=$(CLISRC:.c=.o)
SERVOBJ=$(SERVSRC:.c=.o)

RM=rm -f

INCLPATH=../../include
LIBPATH=../../lib
CFLAGS += -I$(INCLPATH) `pkg-config --cflags gtk+-2.0`
LDFLAGS+= -L$(LIBPATH)
LDLIBS+= -lmy

all: server client

client: $(CLIOBJ)
	cc -o $(CLINAME) $(CLIOBJ) $(LDFLAGS) $(LDLIBS) `pkg-config --cflags --libs gtk+-2.0`

server: $(SERVOBJ)

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(CLINAME)
	-$(RM) $(SERVNAME)

re: fclean all
