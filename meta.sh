#!/bin/bash

# Default CPP file
CPP_FILE="main.cpp"

# Check if a file name is provided, if so, use it instead of the default
if [ ! -z "$1" ]; then
    CPP_FILE="$1"
fi

EXECUTABLE="program"
VERBOSE=false

# Check for the -v flag
if [ "$2" == "-v" ] || [ "$1" == "-v" ]; then
    VERBOSE=true
fi

# Check if the input.txt file exists
if [ ! -f inputm.txt ]; then
    echo "input.txt not found!"
    exit 1
fi

# Compile the C++ file
g++ -o "$EXECUTABLE" "$CPP_FILE"

# Check if the compilation succeeded
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Set memory limit to 1 GB (1048576 KB)
ulimit -v 1048576

# Run the executable with input from input.txt and save to output.txt
if [ "$VERBOSE" = true ]; then
    # Print output to console as well as save it to output.txt
    ./"$EXECUTABLE" < inputm.txt | tee outputm.txt
else
    # Only save output to output.txt
    ./"$EXECUTABLE" < inputm.txt > outputm.txt
fi

# Check if the execution succeeded
if [ $? -ne 0 ]; then
    echo "Execution failed!"
    exit 1
fi

echo "Execution complete. Output saved to output.txt"
