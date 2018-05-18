# `ls(1)` makefile
# Author: Jason Ajmo (jajmo@stevens.edu)

NAME = ls
SRC = ls.c sort.c helpers.c print.c fts_print.c fts_traverse.c

OBJ = $(SRC:.c=.o)
RM = rm -f
CFLAGS += -I./include -Wall -Werror
DFLAGS = -g -DDEBUG
LDLIBS += -lm

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
