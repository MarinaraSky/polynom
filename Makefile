CC=gcc
PROGRAMS=solve
CFLAGS = $(CF) -Wall -Wextra -Wpedantic 
DEBUG_FLAGS = -g3

solve: poly.c main.c
	$(CC) $(CFLAGS) -o $(PROGRAMS) *.c -lm

debug:
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) -o $(PROGRAMS) *.c
clean:
	@rm -f $(PROGRAMS) *.o


