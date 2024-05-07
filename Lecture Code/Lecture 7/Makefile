# File:     Makefile
# Purpose:  Compile single-C-file programs
# Author:   Kerry Veenstra

# List of programs to make
EXECUTABLES = if1 if2 if3 if4 inc1 inc2 inc3 dec1 inc4 dec2

# I added -Wno-misleading-indentation to let if3.c compile.
# Don't use this option in your code.
CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic -Wno-misleading-indentation

.PHONY: all
all: $(EXECUTABLES)

.PHONY: clean
clean: $(EXECUTABLES)
	rm -f $(EXECUTABLES)
