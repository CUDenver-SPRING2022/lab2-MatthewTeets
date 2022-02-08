# Makefile for stream-socket server and client

CC = gcc
OBJCSS = server2.c
OBJCS = client2.c

CFLAGS = -g -Wall

#setup for system
nLIBS = 

all: server2 client2

server2: $(OBJCSS)
	$(CC) $(CFLAGS) -o $@ $(OBJCSS) $(LIBS)
client2: $(OBJCS)
	$(CC) $(CFLAGS) -o $@ $(OBJCS) $(LIBS)

clean:
	rm server2 client2