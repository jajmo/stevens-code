# `crysh(1)` makefile
# Author: Jason Ajmo (jajmo@stevens.edu)

NAME = crysh
SRC = crysh.c decrypt.c execute.c parse.c

OBJ = $(SRC:.c=.o)
RM = rm -f
CFLAGS += -I./include -Wall -Werror -Wpedantic
DFLAGS = -g -DDEBUG
LDLIBS += -lcrypto

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
