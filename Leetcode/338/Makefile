CFLAGS=-g -O2 -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) naive.cpp $(LDFLAGS) -o naive.out
	g++ $(CFLAGS) memoization.cpp $(LDFLAGS) -o memoization.out

clean:
	rm -rf *.o *.out
