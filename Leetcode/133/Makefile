CC=g++
CFLAGS=-I. -ggdb -O2 -std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lm

.PHONY: clean

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<
main.out: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o *.out

