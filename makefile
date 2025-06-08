CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: demo tests

demo: Demo.cpp
	$(CXX) $(CXXFLAGS) -o demo Demo.cpp

tests: tests.cpp
	$(CXX) $(CXXFLAGS) -o tests tests.cpp	

Main: demo
	./demo

test: tests
	./tests

valgrind: tests
	valgrind --leak-check=full --track-origins=yes ./tests

clean:
	rm -f demo tests
.PHONY: all Main tests clean