#Makefile for mynotsominishell

NAME=mynotsominishell
SRC=mynotsominishell.c init_caps.c term_get_cap.c process_input.c my_termprint.c init_terminal.c \
	restore_terminal.c do_cap.c process_char.c rewrite_pos_to_end.c backspace.c history_up.c \
	history_down.c shift_history.c move_cursor_to_pos.c clear_input.c
OBJ=$(SRC:.c=.o)

RM=rm -f

INCLPATH=../include
LIBPATH=../lib
CFLAGS+= -I$(INCLPATH)
LDFLAGS+= -L$(LIBPATH)
LDLIBS+= -lmy -ltermcap

all: $(NAME)

$(NAME):$(OBJ)

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(NAME)

re: fclean all

lib:
	cd ../../src/my && make
	rm ../lib/libmy.a
	cp ../../lib/libmy.a ../lib/
	make re