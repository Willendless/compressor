# Makefile

OBJS = buffer.o main.o symtable.o compressor.o huffman.o decoder.o
CC = gcc
C_FLAGS = -Wall

all: main

main: $(OBJS)
	$(CC) -o $@ $^

.c.o:
	$(CC) $(C_FLAGS) -c -o $@ $<

clean:
	rm -rf *.o  *~  *.out main

rmvim:
	rm *~
