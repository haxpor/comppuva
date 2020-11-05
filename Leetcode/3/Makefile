CC=g++
CFLAGS=-I. -I../input-parser -ggdb -O2 -std=c++17 -Wall -Wextra -pedantic
LDFLAGS=-lm
NAIVE_OBJS=main.o
SLIDING_WINDOW_OBJS=sliding_window.o

.PHONY: all clean

all: main.out sliding_window.out

# compile all source file, we will choose which .o output to use next
%.o: %.cpp ../input-parser/ArrayInputParser.h
	$(CC) -c $(CFLAGS) -o $@ $<
# select which .o to build .out per target
main.out: $(NAIVE_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
sliding_window.out: $(SLIDING_WINDOW_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o *.out

