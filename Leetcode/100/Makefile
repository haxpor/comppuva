CC=g++
CFLAGS=-I. -I../input-parser -ggdb -O2 -std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lm
OBJS=main.o ../input-parser/ArrayInputParser.o
OBJS2=enhanced.o ../input-parser/ArrayInputParser.o

.PHONY: clean

all: main.out enhanced.out
	@echo All done
%.o: %.cpp ../input-parser/ArrayInputParser.h
	$(CC) -c $(CFLAGS) -o $@ $<
main.out: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
enhanced.out: $(OBJS2)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o *.out

