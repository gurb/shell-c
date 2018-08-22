CC = gcc
CFLAGS = -O2 -Wall -pedantic
LIBS = -lm -lnsl

shell: shell.o
	$(CC) $(CFLAGS) $(LIBS) -o shell shell.o
shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c
clean:
	rm -f shell *.o
install: shell
	cp shell /usr/bin
