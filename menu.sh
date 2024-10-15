#!/bin/bash

# Check if the versions directory exists
if [ ! -d "versions" ]; then
    echo "Error: No versions directory found. Save a version first using save.sh."
    exit 1
fi

# Get the list of versions
versions=($(ls versions/))

# Check if there are any versions saved
if [ ${#versions[@]} -eq 0 ]; then
    echo "Error: No versions available."
    exit 1
fi

# Prepend _RESET.cpp if it exists
reset_file="_RESET.cpp"
if [[ " ${versions[@]} " =~ " $reset_file " ]]; then
    versions=("$reset_file" "${versions[@]/$reset_file}")
fi

# Display the versions using fzf for a terminal-like feel
selected_version=$(printf "%s\n" "${versions[@]}" | fzf --height 20 --reverse --border --prompt "Select a version: ")

# Clear the screen
clear

# Restore the selected version if a choice was made
if [ ! -z "$selected_version" ]; then
    # Remove the path prefix to get the file name
    restore_version="versions/$selected_version"
    cp "$restore_version" main.cpp
    echo "Restored main.cpp to version: $selected_version"
else
    echo "No version selected."
fi

# Function to restore main.cpp to the selected version
restore_version() {
    selected_version=$1
    cp "$selected_version" main.cpp
}
