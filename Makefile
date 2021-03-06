CC=gcc
PROGRAMS=solve
CFLAGS = $(CF) -Wall -Wextra -Wpedantic 
DEBUG_FLAGS = -g3


poly.a: poly.o
	ar r poly.a poly.o

poly.o: poly.h poly.c
	$(CC) $(CFLAGS) -c poly.c -lm	

solve: poly.a main.c
	$(CC) $(CFLAGS) -o $(PROGRAMS) *.c -lm

debug:
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) -o $(PROGRAMS) *.c
clean:
	@rm -f $(PROGRAMS) *.o *.a *.h.gch


