#!/bin/bash

# Set the source directory
SOURCE_DIR="$HOME/Downloads"
DEST_FILE="inputm.txt"

# List all .txt files in the Downloads directory
echo "Available .txt files in ~/Downloads:"
mapfile -t txt_files < <(ls "$SOURCE_DIR"/*.txt 2> /dev/null)

# Check if there are no .txt files
if [ ${#txt_files[@]} -eq 0 ]; then
    echo "No .txt files found in ~/Downloads."
    exit 1
fi

# Display the list of .txt files
for i in "${!txt_files[@]}"; do
    echo "$((i + 1)). ${txt_files[i]##*/}" # Print file name without path
done

# Prompt the user to select a file by number
read -p "Select a file by number: " file_number

# Validate the input
if ! [[ "$file_number" =~ ^[1-9][0-9]*$ ]] || [ "$file_number" -le 0 ] || [ "$file_number" -gt "${#txt_files[@]}" ]; then
    echo "Invalid selection."
    exit 1
fi

# Get the selected file
SELECTED_FILE="${txt_files[$((file_number - 1))]}"

# Copy the content of the selected file to input.txt
cp "$SELECTED_FILE" "$DEST_FILE"

# Check if the copy succeeded
if [ $? -eq 0 ]; then
    echo "Successfully copied the content of '${SELECTED_FILE##*/}' to '$DEST_FILE'."
else
    echo "Failed to copy the content."
    exit 1
fi
