CC=g++
CFLAGS=-I. -ggdb -O2 -std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lm
OBJS=main.o ArrayInputParser.o

.PHONY: clean

%.o: %.cpp ArrayInputParser.h
	$(CC) -c $(CFLAGS) -o $@ $<
main.out: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o *.out

