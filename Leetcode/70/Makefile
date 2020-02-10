CFLAGS=-g -O2 -std=c++14
LDFLAGS=-lm

all:
	g++ $(CFLAGS) dp.cpp $(LDFLAGS) -o dp.out
	g++ $(CFLAGS) dp_memoization.cpp $(LDFLAGS) -o dp_memoization.out
	g++ $(CFLAGS) dp_tabulation.cpp $(LDFLAGS) -o dp_tabulation.out
	g++ $(CFLAGS) dp_tabulation_degenerate.cpp $(LDFLAGS) -o dp_tabulation_degenerate.out

clean:
	rm -rf *.o *.out
