#!/bin/bash

# Name of the C++ file
SOURCE_FILE="main.cpp"
# Name of the output executable
OUTPUT_FILE="main.out"

# Compile the C++ file with precompiled header
echo "Compiling $SOURCE_FILE..."
g++ -include pch.h "$SOURCE_FILE" -o "$OUTPUT_FILE"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    echo "====================== OUTPUT ======================"
    ./"$OUTPUT_FILE"
    echo "===================================================="
else
    echo "Compilation failed."
fi
