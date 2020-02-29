CC=g++
CFLAGS=-I. -I../input-parser -ggdb -O2 -std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lm
OBJS=main.o ../input-parser/ArrayInputParser.o

.PHONY: clean

%.o: %.cpp ../input-parser/ArrayInputParser.cpp
	$(CC) -c $(CFLAGS) -o $@ $<
main.out: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o *.out

