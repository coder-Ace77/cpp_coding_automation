#!/bin/bash

# Function to check if lib folder exists, if not create it
create_lib_folder() {
    if [ ! -d "lib" ]; then
        echo "Creating 'lib' directory..."
        mkdir lib
    fi
}

# Function to save content from lib_input.cpp to a file in the lib folder
save_input_to_lib() {
    local input_file="lib_input.cpp"
    
    if [ ! -f "$input_file" ]; then
        echo "Error: $input_file not found."
        exit 1
    fi

    # Read content from lib_input.cpp
    content=$(<"$input_file")

    # Ask the user for the file name to save in lib folder
    read -p "Enter the name of the file to save in the 'lib' folder (e.g., module1.cpp): " file_name

    # Full path to the file inside the lib folder
    local file_path="lib/$file_name"

    # Save the content to the specified file
    echo "$content" > "$file_path"    
    # Return the file name to the caller
    echo "$file_path"
}

# Function to map module name to file in .data file
map_module_to_file() {
    local file_name="$1"
    local data_file="lib/.data"
    
    # Ask for module name
    read -p "Enter the module name: " module_name

    # Append module mapping to .data file
    echo "$module_name,$file_name" >> "$data_file"

    echo "Module '$module_name' mapped to '$file_name' in $data_file."
}

# Function to update an existing module without creating new files
update_module() {
    local data_file="lib/.data"
    
    if [ ! -f "$data_file" ]; then
        echo "Error: No .data file found."
        exit 1
    fi

    # Select module using fzf
    selected_module=$(cat "$data_file" | fzf --delimiter=',' --with-nth=1)

    if [ -z "$selected_module" ]; then
        echo "No module selected. Aborting."
        exit 0
    fi

    # Extract module name and file name
    module_name=$(echo "$selected_module" | cut -d ',' -f 1)
    old_file_name=$(echo "$selected_module" | cut -d ',' -f 2)

    content=$(<lib_input.cpp)
    echo "$content" > "$old_file_name"

    echo "Module '$module_name' updated with new content from lib_input.cpp."
}

# Main script execution
create_lib_folder

# Check if -u flag is passed for update mode
if [ "$1" == "-u" ]; then
    update_module
else
    # Step 1: Save the input content from lib_input.cpp to a file in the lib folder
    file_name=$(save_input_to_lib)

    # Step 2: Map the module name to the file in the .data file in the lib folder
    map_module_to_file "$file_name"
fi
