CFLAGS=-g -O2 -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) recursive.cpp $(LDFLAGS) -o recursive.out
	g++ $(CFLAGS) recursive_lookup.cpp $(LDFLAGS) -o recursive_lookup.out
	g++ $(CFLAGS) dp.cpp $(LDFLAGS) -o dp.out

clean:
	rm -rf *.o *.out
