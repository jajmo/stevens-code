NAME = mysort
TARBALL = jajmo-$(NAME).tar.gz
SRC = select.cpp swap.cpp intintCompare.cpp strstrCompare.cpp uintVal.cpp main.cpp merge.cpp mergeRecurse.cpp shell.cpp insert2.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	g++ $(OBJ) -o $(NAME)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all

submit: fclean
	tar cvzf $(TARBALL) *


