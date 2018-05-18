NAME = FinalProject
TARBALL = jajmo-dcrouche-$(NAME).tar.gz
SRC = main.cpp \
	\
	heist_map_neighbors.cpp \
	heist_map_const_dest.cpp \
	heist_map_get_add.cpp \
	heist_map_print_functions.cpp \
	heist_map_dfs_fap.cpp \
	heist_map_initialize.cpp \
	heist_map_process_input.cpp \
	heist_map_safest_paths.cpp \
	heist_map_escape_routes.cpp \
	heist_map_unvisit_all.cpp \
	heist_map_one_man_job.cpp \
	heist_map_big_job_crew_selector.cpp

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
	-$(RM) $(NAME).exe
	-$(RM) $(TARBALL)

re: fclean all

submit: fclean
	tar cvzf $(TARBALL) *
