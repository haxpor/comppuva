CFLAGS=-g -O2 -Wall -Wextra -pedantic -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) naive.cpp $(LDFLAGS) -o naive.out
	g++ $(CFLAGS) dp_topdown.cpp $(LDFLAGS) -o dp_topdown.out

clean:
	rm -rf *.o *.out
