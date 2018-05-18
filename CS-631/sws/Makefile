# `sws(1)` Unix makefile

NAME = sws
.include <MakeTargets>

CC = gcc
OBJ = $(SRC:.c=.o)
RM = rm -f
DFLAGS = -g -DDEBUG
CFLAGS += -I./include -Wall -Werror
LDLIBS += -lmagic

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
