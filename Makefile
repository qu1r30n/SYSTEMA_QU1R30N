# simple Makefile for SYSTEMA_QU1R30N
# usage:
#   make        # build ejecutable "sistema.exe"
#   make clean  # remove objects and executable

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I.

# collect all C sources under the project tree
SRC := $(wildcard *.c) \
       $(wildcard modelos/**/*.c) \
       $(wildcard procesos/**/*.c) \
       $(wildcard cabeceras/**/*.c)

OBJ := $(SRC:.c=.o)

all: sistema.exe

sistema.exe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# generic rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) sistema.exe

.PHONY: all clean
