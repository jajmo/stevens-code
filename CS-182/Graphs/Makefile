NAME = graphs
TARBALL = jajmo-$(NAME).tar.gz
SRC = myamgraph.hh mygraphs.hh am_constructor.cpp destructors.cpp edges.cpp getters.cpp graph_constructor.cpp main.cpp neighbors.cpp print_functions.cpp searches.cpp verticies.cpp 
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
