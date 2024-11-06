#!/bin/bash

cd /home/acecoder/Desktop/script
current_hash=$(sha256sum main.cpp | awk '{ print $1 }')

if [ -f last_hash.txt ]; then
    last_hash=$(cat last_hash.txt)
else
    last_hash=""
fi

if [ "$current_hash" == "$last_hash" ]; then
    echo "[No changes detected in main.cpp. Skipping compilation.]"
else
    echo "[Linking.]"
    python3 linker.py
    if [ $? -ne 0 ]; then
        echo "[Linking failed. Aborting compilation.]"
        exit 0
    fi
    
    echo "[Changes detected. Compiling main.cpp]"
    g++ -std=c++17 main.cpp -include pch.h -o main
    if [ $? -ne 0 ]; then
        echo "[Compilation failed]"
        exit 0
    fi
    
    echo "$current_hash" > last_hash.txt
    echo "[Compiled.]"
fi

echo "[Executing]"

timeout 3s /usr/bin/time -f "\nExecution time: %e seconds\nMemory used: %M KB\n" ./main print_dollar < input.txt | python3 script.py

if [ $? -eq 124 ]; then
    echo "TLE: Time Limit Exceeded"
    exit 0
fi
