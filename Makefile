CC = cc
CFLAGS = -std=c99 -pedantic -Wall -g -I. -L. -lsvm

.PHONY: all
all:
	DYLD_LIBRARY_PATH=. $(CC) ${CFLAGS} -o demo demo.c
