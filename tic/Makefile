OBJS = main.o ticboard.o
CC=gcc
CFLAGS=-g -c -Wall -O0
LFLAGS=-lncurses -o

# The default rule - compiling our main program:
all:	tic
		echo all: make complete

tic: $(OBJS)
	$(CC) $(LFLAGS) $@ $+
#$(CC) $(LFLAGS) $@ $+ -Wl

# Tell make how to build .o files from .cpp files:
%.o:%.c
	$(CC) $(CFLAGS) $+

#Now make sure that make rebuilds files if included headers change:
$(OBJS): $(HEADERS)

clean:
	rm -f tic *.o *.map *.gch
	
