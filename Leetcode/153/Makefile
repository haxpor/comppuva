CFLAGS=-O2 -g
LDFLAGS=-lm

all:
	g++ $(CFLAGS) naive.cpp $(LDFLAGS) -o naive.out
	g++ $(CFLAGS) bisect.cpp $(LDFLAGS) -o bisect.out

clean:
	rm -rf *.o *.out
