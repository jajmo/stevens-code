#Makefile for pipes

NAME=pipes
SRC=pipes.c

OBJ=$(SRC:.c=.o)
RM=rm -f
INCLPATH=../../include
LIBPATH=../../lib
CFLAGS+= -I$(INCLPATH)
LDFLAGS+= -L$(LIBPATH)
LDLIBS+= -lmy

all: my $(NAME)

$(NAME):$(OBJ)

my:
	cd ../my && make

myclean:
	cd ../my && make fclean

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: myclean clean
	-$(RM)
	-$(RM) $(NAME)

re: fclean all
