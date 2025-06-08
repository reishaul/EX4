#reishaul1@gmail.com
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

#all targets
all: demo tests

#build the demo object files
demo: Demo.cpp
	$(CXX) $(CXXFLAGS) -o demo Demo.cpp

#build the tests object files
tests: tests.cpp
	$(CXX) $(CXXFLAGS) -o tests tests.cpp	

# Define the main target to run the demo and tests
Main: demo
	./demo

test: tests
	./tests
# Run tests with Valgrind
valgrind: tests
	valgrind --leak-check=full --track-origins=yes ./tests 

# Run valgrind on the demo executable
valgrind_demo: demo
	valgrind --leak-check=full --track-origins=yes ./demo

# Clean up the build artifacts
clean:
	rm -f demo tests
.PHONY: all Main tests clean