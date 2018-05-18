lib: cleanlib
	cd libgreet && \
	cc -Wall -Werror -c -fPIC greet.c && \
	cc -shared -Wl,-soname,libgreet.so.1 -o libgreet.so.1.0 greet.o && \
	ln -s libgreet.so.1.0 libgreet.so.1 && \
	ln -s libgreet.so.1.0 libgreet.so

re: clean lib

clean: cleanlib
	-rm -f a.out hello.o

cleanlib:
	-rm -f libgreet/libgreet.so*
	-rm -f libgreet/greet.o