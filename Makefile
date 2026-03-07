# simple Makefile for SYSTEMA_QU1R30N
# usage:
#   make        # build ejecutable "sistema.exe"
#   make clean  # remove objects and executable

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I.

# recursive wildcard helper (GNU Make portable)
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# collect all C sources under the project tree
SRC := $(call rwildcard,./,*.c)

# pre.c is a scratch/legacy file and should not be linked into production build
SRC := $(filter-out ./pre.c,$(SRC))

OBJ := $(SRC:.c=.o)

all: sistema.exe

sistema.exe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# generic rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) sistema.exe

.PHONY: all clean
