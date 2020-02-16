CFLAGS=-g -O2 -Wall -Wextra -pedantic -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) dp_memo.cpp $(LDFLAGS) -o dp_memo.out
	g++ $(CFLAGS) dp_iterative.cpp $(LDFLAGS) -o dp_iterative.out

clean:
	rm -rf *.o *.out
