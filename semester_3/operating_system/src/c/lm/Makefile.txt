CC=gcc
CFLAGS=-Wall

all: lmc lmd

lmc: lmc.c
	$(CC) $(CFLAGS) -o lmc lmc.c

lmd: lmd.c
	$(CC) $(CFLAGS) -D_REENTRANT -lpthread -o lmd lmd.c

clean:
	rm -f lmc lmd core

listen:
	nc -l -p 12345

