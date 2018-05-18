# Generic Makefile for compiling an application using OpenGL
#
# Do NOT copy and paste this file, but rather save it, as make(1) depends on
# tabs -- copy and paste would turn those into normal whitespace
#
# $Author: jschauma $
# $Id: Makefile,v 1.2 2002/12/04 22:02:13 jschauma Exp $

# replace <hwk1a> with the name of the executable to create
TARGET          = threads

# List the object-files needed;  usually, these are the names of the
# source-files with the ending substituted with ".o"
# If your program uses the files main.c and hwk1a.c, then this line would be
OFILES          = src/main.o \
				  src/create_product.o \
				  src/producer.o \
				  src/consumer.o \
				  src/fib.o

# specify the compiler to use.  If you are writing in C, this should probably
# be left untouched (unless you specifically want to compile the application
# on IRIX using the native compiler, in which case it would be 'cc').  If you
# are writing you program in C++, use 'g++'
CC              = g++

# Common flags passed to the compiler while compiling:
# -Wall: 	display _all_ warnings (does not work with IRIX cc compiler!
# 		use '-fullwarn' instead)
# -g:    	produce debugging information
CFLAGS          = -Wall -g

# Libraries to link with.
# See libefence(3) for details on the efence library (useful for debugging
# memory allocation)
LDFLAGS		=  -lX11 -lXmu -lm -lrt

# Common prefixes on our machines.
PREFIX		= /usr/pkg
X11PREFIX	= /usr/X11R6

# Where to find the header files.
INCLUDES        = -I${X11PREFIX}/include -I${PREFIX}/include -I. -Iinclude/

# Where to find the libraries
LIBDIRS         = -L${X11PREFIX}/lib -L${PREFIX}/lib -pthread

# the famous 'all' target, invoked if you type 'make' or 'make all'
all: ${TARGET}

# TARGET depends on the object files, created through the
# .c.o: rule.  It then calls the compiler to link the object-files into the
# executable.  Note that library parameters are position sensitive.
${TARGET}: ${OFILES}
	${CC} ${LIBDIRS} ${OFILES} -o ${TARGET} ${LDFLAGS}

# automatically compile each .c-file or .cpp-file into a .o-object file
.cpp.o .c.o:
	${CC} ${INCLUDES} ${CFLAGS} -c $< -o $@

# rm object files and executable before compiling everything from scratch or
# before submitting your work
clean:
	rm -f ${OFILES} ${TARGET} Makefile.bak

re: clean all

# You may issue 'make depend' to generate an automatic list of dependencies
# Note that 'make depend' will add a bunch of lines below the last line, which
# MUST NOT be removed.  The original Makefile will be saved as 'Makefile.bak'
MKDPDFLAGS	= -- ${CFLAGS} ${INCLUDES} -- *.c *.cpp

# Note: makedepend(1) lives in /usr/bin/X11/ on guinness, which may not be in
# your PATH
MKDPD		= makedepend

depend:
	${MKDPD} ${MKDPDFLAGS}

# DO NOT DELETE THIS LINE -- make depends on it.
