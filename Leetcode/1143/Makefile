CFLAGS=-g -O2 -Wall -Wextra -pedantic -Wshadow -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) recursive.cpp $(LDFLAGS) -o recursive.out
	g++ $(CFLAGS) dp.cpp $(LDFLAGS) -o dp.out
	g++ $(CFLAGS) dp_memoization.cpp $(LDFLAGS) -o dp_memoization.out
	g++ $(CFLAGS) dp_tabulation.cpp $(LDFLAGS) -o dp_tabulation.out

clean:
	rm -rf *.o *.out
