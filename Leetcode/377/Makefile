CFLAGS=-g -O2 -Wall -Wextra -pedantic -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) dp_topdown.cpp $(LDFLAGS) -o dp_topdown.out
	g++ $(CFLAGS) dp_bottomup.cpp $(LDFLAGS) -o dp_bottomup.out

clean:
	rm -rf *.o *.out
