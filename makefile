CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = demo
SRC = Demo.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

Main: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
