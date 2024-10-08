#!/bin/bash

# Check if a version name is provided
if [ -z "$1" ]; then
    echo "Error: You must provide a version name."
    exit 1
fi

# Create the versions directory if it doesn't exist
mkdir -p versions

# Save the current main.cpp with the version name
cp main.cpp "versions/main_$1.cpp"
if [ $? -ne 0 ]; then
    echo "Error: Failed to save the version."
    exit 1
fi

echo "Version '$1' saved successfully!"
