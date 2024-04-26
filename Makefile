CXX = g++
CXXFLAGS = -Wall -Werror -g -std=c++14

TARGET = fft

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(^) -o $(TARGET)
clean:
	rm -f $(OBJECTS) $(TARGET)