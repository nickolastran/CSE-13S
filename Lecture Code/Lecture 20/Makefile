# File:     Makefile
# Purpose:  Compile single-C-file programs
# Author:   Kerry Veenstra

# List of programs to make
EXECUTABLES = array1 array2 array3 array4 array5 array6

CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LFLAGS = -lm

# Append flags to CFLAGS only if making the "debug" target.
debug: CFLAGS += -g -D DEBUG=1

.PHONY: all debug
# Listing the "all" target first makes it the default target when typing "make"
all: $(EXECUTABLES)
debug: $(EXECUTABLES)

.PHONY: clean
clean: $(EXECUTABLES)
	rm -f $(EXECUTABLES) *.o
