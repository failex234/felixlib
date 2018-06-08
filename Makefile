CC=gcc
CCFLAGS=-Wall

all:
	make -C src

clean:
	make clean -C src
