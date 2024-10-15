#!/bin/bash

cd /home/acecoder/Desktop/script
current_hash=$(sha256sum main.cpp | awk '{ print $1 }')

if [ -f last_hash.txt ]; then
    last_hash=$(cat last_hash.txt)
else
    last_hash=""
fi

if [ "$current_hash" == "$last_hash" ]; then
    echo "No changes detected in main.cpp. Skipping compilation."
else
    python3 linker.py
    echo "Changes detected. Compiling main.cpp..."
    g++ main.cpp -o main
    if [ $? -ne 0 ]; then
        echo -e "\e[31mCompilation failed\e[0m"
        exit 1
    fi
    
    echo "$current_hash" > last_hash.txt
    echo "Compiled"
fi

echo "Executing..."

timeout 3s /usr/bin/time -f "\nExecution time: %e seconds\nMemory used: %M KB\n" ./main print_dollar < input.txt | python3 script.py
if [ $? -eq 124 ]; then
    echo "TLE: Time Limit Exceeded"
    exit 0
fi
