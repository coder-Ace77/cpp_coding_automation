#!/bin/bash

sed -i 's|// cout<<\"\$\"<<endl;|cout<<\"\$\"<<endl;|' main.cpp
current_hash=$(sha256sum main.cpp | awk '{ print $1 }')

if [ -f last_hash.txt ]; then
    last_hash=$(cat last_hash.txt)
else
    last_hash=""
fi

if [ "$current_hash" == "$last_hash" ]; then
    echo "No changes detected in main.cpp. Skipping compilation."
else
    echo "Changes detected. Compiling main.cpp..."
    g++ main.cpp -o main
    if [ $? -ne 0 ]; then
        echo "Compilation failed"
        exit 1
    fi
    
    echo "$current_hash" > last_hash.txt
    echo "Compiled"
fi

./main < input.txt | python3 script.py
if [ $? -ne 0 ]; then
    echo "Execution failed"
    exit 1
fi

sed -i 's|cout<<\"\$\"<<endl;|// cout<<\"\$\"<<endl;|' main.cpp
