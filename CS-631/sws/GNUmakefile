# `sws(1)` GNU makefile
#Just checking push
#Just checking another push in this file


NAME = sws
include MakeTargets

OS = $(shell uname)
CC = gcc
OBJ = $(SRC:.c=.o)
RM = rm -f
DFLAGS = -g -DDEBUG

ifeq ($(OS),Linux)
	LDLIBS += -L/lib64/bsd -lbsd -lmagic
	CFLAGS += -I./include -I../libbsd/include -I../libmagic/src  -Wall -Werror
else
	LDLIBS += -L/opt/csw/lib/ -R/opt/csw/lib/ -lsocket -lnsl -lmagic
	CFLAGS += -I./include  -I/opt/csw/include/ -Wall -Werror
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS)

debug: fclean
	$(CC) $(CFLAGS) $(DFLAGS) $(LDFLAGS) $(LDLIBS) -c $(SRC)
	$(CC) $(DFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(NAME)


re: fclean all
