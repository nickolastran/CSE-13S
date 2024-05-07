# File:     Makefile
# Purpose:  Compile single-C-file programs
# Author:   Kerry Veenstra

# List of programs to make
EXECUTABLES = ma1 ma2 ma3 ma4 ma5 ma6 struct1 struct2 list1 list2

CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LFLAGS = -lm

.PHONY: all debug
# Listing the "all" target first makes it the default target when typing "make"
all: $(EXECUTABLES)
debug: $(EXECUTABLES)

# Append flags to CFLAGS only if making the "debug" target.
debug: CFLAGS += -g -D DEBUG=1

ma1: ma1.o
	$(CC) $^ $(LFLAGS) -o $@

ma2: ma2.o
	$(CC) $^ $(LFLAGS) -o $@

ma3: ma3.o
	$(CC) $^ $(LFLAGS) -o $@

ma4: ma4.o
	$(CC) $^ $(LFLAGS) -o $@

ma5: ma5.o
	$(CC) $^ $(LFLAGS) -o $@

ma6: ma6.o
	$(CC) $^ $(LFLAGS) -o $@

struct1: struct1.o
	$(CC) $^ $(LFLAGS) -o $@

struct2: struct2.o
	$(CC) $^ $(LFLAGS) -o $@

list1: list1.o
	$(CC) $^ $(LFLAGS) -o $@

list2: list2.o
	$(CC) $^ $(LFLAGS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean: $(EXECUTABLES)
	rm -f $(EXECUTABLES) *.o
