#Makefile for libmy.a

NAME=libmy.a
SRC=my_alpha.c my_char.c my_digits.c my_int.c \
	my_num_base.c my_revstr.c my_str.c my_strcat.c \
	my_strcmp.c my_strconcat.c my_strcpy.c my_strdup.c \
	my_strfind.c my_strlen.c my_strnconcat.c my_strncpy.c \
	my_strpos.c my_strrfind.c my_strrpos.c xmalloc.c \
	my_strncmp.c my_vect2str.c my_str2vect.c my_freevect.c \
	my_atoi.c
OBJ=$(SRC:.c=.o)
RM=rm -f
INCLPATH=../../include
LIBPATH=../../lib
CFLAGS+= -I$(INCLPATH)

all: $(OBJ)
	ar -rc $(LIBPATH)/$(NAME) $(OBJ)
	ranlib $(LIBPATH)/$(NAME)

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(LIBPATH)/$(NAME)

re: fclean all
