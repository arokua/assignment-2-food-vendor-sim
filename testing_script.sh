#!/bin/bash

# Variables
PROGRAM="./ftt"
DATA_DIR="data-files"
TESTING_DIR="testing-files"

DATA_FILE_1="foods.dat"
DATA_FILE_2="coins.dat"

BASE_NAME_1=$(basename "${DATA_FILE_1%.*}")
EXTENSION_1="${DATA_FILE_1##*.}"
DATA_FILE_1_COPY="${BASE_NAME_1}_copy.${EXTENSION_1}"
BASE_NAME_2=$(basename "${DATA_FILE_2%.*}")
EXTENSION_2="${DATA_FILE_2##*.}"
DATA_FILE_2_COPY="${BASE_NAME_2}_copy.${EXTENSION_2}"

INPUT_FILES=$(ls ${TESTING_DIR}/input_testcase_*)
EXPECTED_OUTPUT_FILES=$(ls ${TESTING_DIR}/expected_output_*)

# Function to copy data files
if [ ! -d "${DATA_DIR}" ]; then
    echo "Data directory not found: ${DATA_DIR}"
    exit 1
fi
if [ ! -f "${DATA_DIR}/${DATA_FILE_1}" ]; then
    echo "Data file not found: ${DATA_FILE_1}"
    exit 1
fi
if [ ! -f "${DATA_DIR}/${DATA_FILE_2}" ]; then
    echo "Data file not found: ${DATA_FILE_2}"
    exit 1
fi
cp "${DATA_DIR}/${DATA_FILE_1}" "${DATA_FILE_1_COPY}"
cp "${DATA_DIR}/${DATA_FILE_2}" "${DATA_FILE_2_COPY}"
mv "${DATA_FILE_1_COPY}" "${TESTING_DIR}"
mv "${DATA_FILE_2_COPY}" "${TESTING_DIR}"


# The directory you expect to be in, relative to the script's location
EXPECTED_DIR="$(dirname "$0")/../assignment-2-cosc1076"

# Get the current directory
CURRENT_DIR=$(pwd)

# Convert expected directory to an absolute path
EXPECTED_DIR=$(cd "$EXPECTED_DIR"; pwd)

# Check if the current directory is the expected one
if [ "$CURRENT_DIR" != "$EXPECTED_DIR" ]; then
    echo "Error: not in the expected directory"
    exit 1
fi

make
# Function to run tests
echo "Running tests..."
for i in ${INPUT_FILES}; do
    echo "Running test with input file: ${i}"
    number=$(basename ${i} | sed 's/[^0-9]//g')
    ${PROGRAM} "${TESTING_DIR}/${DATA_FILE_1_COPY}" "${TESTING_DIR}/${DATA_FILE_2_COPY}" < ${i} > "${TESTING_DIR}/actual_output_${number}.txt"
    diff -w "${TESTING_DIR}/actual_output_${number}.txt" "${TESTING_DIR}/expected_output_${number}.txt"
    if [ $? -ne 0 ]; then
        echo "Test failed for input file: ${i}"
    else
        echo "Test passed for input file: ${i}"
    fi
    echo
done
