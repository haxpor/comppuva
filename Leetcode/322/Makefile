CFLAGS=-g -O2 -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) naive.cpp $(LDFLAGS) -o naive.out
	g++ $(CFLAGS) dp_topdown.cpp $(LDFLAGS) -o dp_topdown.out
	g++ $(CFLAGS) dp_bottomup.cpp $(LDFLAGS) -o dp_bottomup.out

clean:
	rm -rf *.o *.out
