# Makefile

CC = gcc
CFlag = -Wall

all: random

random: main.o
	$(CC) -o $@ $^ -lm

main.o: main.c
	$(CC) $(CFlag) -c -o $@ $< -lm

clean:
	rm -rf *.o *.txt

clean_exe:
	rm -rf *.o *.txt random

