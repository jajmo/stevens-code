#Makefile for various tests
RM=rm -f
INCLPATH=../include
LIBPATH=../lib

#libmy variables
SRCMY=testmy.c
LIBMY=my
MYNAME=mytest

#libmylist variables
SRCLIST=testmylist.c
LIBLIST=mylist
LISTNAME=mylisttest

clean:
	-$(RM) *.o
	-$(RM) *.swp
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core
	-$(RM) $(MYNAME)
	-$(RM) $(LISTNAME)

lib:
	cd ../src/$(LIBMY) && make
	cd ../src/$(LIBLIST) && make

libmy: lib
	cc -I$(INCLPATH) -L$(LIBPATH) $(SRCMY) -l$(LIBMY) -o $(MYNAME)

liblist: lib
	cc -I$(INCLPATH) -L$(LIBPATH) $(SRCLIST) -l$(LIBLIST) -l$(LIBMY) -o $(LISTNAME)

fclean: clean
	cd ../src/$(LIBMY) && make fclean
	cd ../src/$(LIBLIST) && make fclean

allclean: clean
	cd ../src/$(LIBMY) && make clean
	cd ../src/$(LIBLIST) && make clean
