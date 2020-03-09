CC=g++
CFLAGS=-I. -I../input-parser -ggdb -std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lm
OBJS_iterative=iterative.o ../input-parser/ArrayInputParser.o
OBJS_recursive=recursive.o ../input-parser/ArrayInputParser.o

.PHONY: clean

%.o: %.cpp ../input-parser/ArrayInputParser.h
	$(CC) -c $(CFLAGS) -o $@ $<
iterative.out: $(OBJS_iterative)
	$(CC) -o $@ $^ $(LDFLAGS)
recursive.out: $(OBJS_recursive)
	$(CC) -o $@ $^ $(LDFLAGS)
all: iterative.out recursive.out
	@echo "All done"

clean:
	rm -rf *.o *.out

