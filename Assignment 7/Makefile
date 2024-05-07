CC=gcc
CFLAGS=-Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
 
HEADERS = bitreader.h bitwriter.h node.h pq.h
LDFLAGS =  -lm
EXEC = huff
EXEC2 = dehuff
EXEC3 = brtest
EXEC4 = bwtest
EXEC5 = nodetest
EXEC6 = pqtest

all:	CFLAGS = $(BASICS)
debug:  CFLAGS = $(BASICS)

all: $(EXEC) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6)

$(EXEC): $(EXEC).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@

$(EXEC2): $(EXEC2).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@

$(EXEC3): $(EXEC3).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@

$(EXEC4): $(EXEC4).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@

$(EXEC5): $(EXEC5).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@

$(EXEC6): $(EXEC6).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: clean format scan-build
