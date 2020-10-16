CC=g++
LDFLAGS=-lm

CFLAGS=-I. -I../input-parser -ggdb -O2 -std=c++11 -Wall -Wextra -pedantic
CFLAGS_DEBUG=-I. -I../input-parser -ggdb -std=c++11 -Wall -Wextra -pedantic -DDEBUG

OBJS=main.o
OBJS_DEBUG=main.do

.PHONY: clean

all: main.out
debug: main-debug.out

%.o: %.cpp ../input-parser/ArrayInputParser.h
	$(CC) -c $(CFLAGS) -o $@ $<
%.do: %.cpp ../input-parser/ArrayInputParser.h
	$(CC) -c $(CFLAGS_DEBUG) -o $@ $<

main.out: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
main-debug.out: $(OBJS_DEBUG)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.do *.o *.out

