CXX = g++
CXXFLAGS = -Wall -Werror -g -std=c++14

TARGET = ftt

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Define test data pattern
TEST_FILES = coins.dat food.dat
EXPECTED_OUTPUT = expect1.dat.out
NUM_TESTS = 1
# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(^) -o $(TARGET)

# Phony target to run all tests
test:
	@echo "Running test with files: $(TEST_FILES)"
	@if [ $(words $(TEST_FILES)) -eq 3 ]; then \
		./fft $(word 1, $(TEST_FILES)) $(word 2, $(TEST_FILES)) < $(word 3, $(TEST_FILES)) > combined_output.out; \
	elif [ $(words $(TEST_FILES)) -eq 2 ]; then \
		./fft $(word 1, $(TEST_FILES)) $(word 2, $(TEST_FILES)) > combined_output.out; \
	else \
		echo "Incorrect number of input files."; \
	fi
	diff -s combined_output.out $(EXPECTED_OUTPUT)

clean:
	rm -f $(OBJECTS) $(TARGET)
