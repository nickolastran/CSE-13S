# File:     Makefile
# Purpose:  Compile single-C-file programs
# Author:   Kerry Veenstra

# List of programs to make
EXECUTABLES = ty1 fp1 db1 sb1 nan1

CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LFLAGS = -lm

.PHONY: all debug
# Listing the "all" target first makes it the default target when typing "make"
all: $(EXECUTABLES)
debug: $(EXECUTABLES)

# Append flags to CFLAGS only if making the "debug" target.
debug: CFLAGS += -g -D DEBUG=1

nan1: nan1.o
	$(CC) $^ $(LFLAGS) -o $@

db1: db1.o
	$(CC) $^ $(LFLAGS) -o $@

ty1: ty1.o
	$(CC) $^ $(LFLAGS) -o $@

fp1: fp1.o
	$(CC) $^ $(LFLAGS) -o $@

sb1: sb1.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean: $(EXECUTABLES)
	rm -f $(EXECUTABLES) *.o
