CC=g++
CFLAGS=-I. -I../input-parser -ggdb -O2 -std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lm
OBJS=main.o ../input-parser/ArrayInputParser.o
OBJS2=faster.o ../input-parser/ArrayInputParser.o
OBJS2=iterative.o ../input-parser/ArrayInputParser.o

.PHONY: clean

all: main.out faster.out iterative.out
	@echo All done
%.o: %.cpp ../input-parser/ArrayInputParser.h
	$(CC) -c $(CFLAGS) -o $@ $<
main.out: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
faster.out: $(OBJS2)
	$(CC) -o $@ $^ $(LDFLAGS)
iterative.out: $(OBJS2)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o *.out

