NAME = graphs
TARBALL = jajmo-$(NAME).tar.gz
SRC = main.cpp myamgraph.cpp mygraph.cpp utility_functions.cpp union_find.cpp kruskal.cpp prims.cpp dijkstra.cpp floyd.cpp ford_fulkerson.cpp fap.cpp show_max_flow.cpp
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
