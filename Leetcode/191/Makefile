CFLAGS=-g -O2 -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) main.cpp $(LDFLAGS) -o main.out
	g++ $(CFLAGS) mask.cpp $(LDFLAGS) -o mask.out
	g++ $(CFLAGS) popcount.cpp $(LDFLAGS) -o popcount.out

clean:
	rm -rf *.o *.out
