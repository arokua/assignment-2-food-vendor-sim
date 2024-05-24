CXX = g++
CXXFLAGS = -Wall -Werror -g -std=c++14

TARGET = ftt

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

DATA_DIR = data-files
TESTING_DIR = testing-files
PROGRAM = ./ftt

DATA_FILE_1 = foods.dat
DATA_FILE_2 = coins.dat
BASE_NAME_1 = $(basename $(DATA_FILE_1))
BASE_NAME_2 = $(basename $(DATA_FILE_2))
EXTENSION = $(suffix $(DATA_FILE_1))
DATA_FILE_1_COPY = $(BASE_NAME_1)_copy$(EXTENSION)
DATA_FILE_2_COPY = $(BASE_NAME_2)_copy$(EXTENSION)

INPUT_FILES = $(wildcard $(TESTING_DIR)/input_testcase_*)
EXPECTED_OUTPUT_FILES = $(wildcard $(TESTING_DIR)/expected_output_*)
ACTUAL_OUTPUT_FILES = $(patsubst $(TESTING_DIR)/input_testcase_%, $(TESTING_DIR)/actual_output_%, $(INPUT_FILES))

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Valgrind test
val:
	valgrind --tool=memcheck --log-file=valrep.txt --leak-check=full \
	--track-origins=yes -v ./$(TARGET) $(DATA_DIR)/$(DATA_FILE_1) $(DATA_DIR)/$(DATA_FILE_2)

# Test target to run all tests
.PHONY: test
test:
	@echo "Running tests..."
	@$(foreach i, $(INPUT_FILES), \
		echo "Running test with input file: $(i)"; \
		number=`basename $(i) | sed 's/[^0-9]//g'`; \
		./$(PROGRAM) $(TESTING_DIR)/$(DATA_FILE_1_COPY) $(TESTING_DIR)/$(DATA_FILE_2_COPY) < $(i) > $(TESTING_DIR)/actual_output_$$number.txt; \
		ACTUAL_OUTPUT_FILES+="actual_output_$$number.txt"; \
		diff -w $(TESTING_DIR)/actual_output_$$number.txt $(TESTING_DIR)/expected_output_$$number.txt; \
		if [ $$? -ne 0 ]; then \
			echo "Test failed for input file: $(i)"; \
		else \
			echo "Test passed for input file: $(i)"; \
		fi; \
	)

# Copy data files to the testing folder
copy:
	@if [ ! -d "$(DATA_DIR)" ]; then \
		echo "Data directory not found: $(DATA_DIR)"; \
		exit 1; \
	fi
	@if [ ! -f "$(DATA_DIR)/$(DATA_FILE_1)" ]; then \
		echo "Data file not found: $(DATA_FILE_1)"; \
		exit 1; \
	fi
	@if [ ! -f "$(DATA_DIR)/$(DATA_FILE_2)" ]; then \
		echo "Data file not found: $(DATA_FILE_2)"; \
		exit 1; \
	fi
	cp "$(DATA_DIR)/$(DATA_FILE_1)" "$(DATA_FILE_1_COPY)"
	cp "$(DATA_DIR)/$(DATA_FILE_2)" "$(DATA_FILE_2_COPY)"
	mv "$(DATA_FILE_1_COPY)" "$(TESTING_DIR)"
	mv "$(DATA_FILE_2_COPY)" "$(TESTING_DIR)"

# Clean target
clean:
	rm -f $(OBJECTS) $(TARGET) $(TESTING_DIR)/$(DATA_FILE_1_COPY) $(TESTING_DIR)/$(DATA_FILE_2_COPY) $(ACTUAL_OUTPUT_FILES)
