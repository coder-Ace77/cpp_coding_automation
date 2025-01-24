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
    python3 linker.py
    if [ $? -ne 0 ]; then
        echo "[Linking failed. Aborting compilation.]"
        exit 0
    fi

    # Capture compilation error output
    # compilation_output=$( (/usr/bin/time -f "%e" g++ -std=c++17 main.cpp -include pch.h -o main) 2>&1 )
    compilation_output=$( (/usr/bin/time -f "%e" g++ -include pch.h main.cpp -o main) 2>&1 )
    if [ $? -ne 0 ]; then
        echo "[Compilation failed]"
        echo "$compilation_output"
        exit 0
    fi

    # Calculate and display compilation time
    compilation_time_ms=$(awk "BEGIN {printf \"%.0f\", $compilation_output * 1000}")
    echo -e "\n[Compiled] ${compilation_time_ms} ms"
    echo "$current_hash" > last_hash.txt
fi

echo "[Executing]"
# timeout 3s /usr/bin/time -f "\nExecution time: %e seconds" ./main print_dollar < input.txt | python3 script.py
x=$(timeout 3s /usr/bin/time -f "\n[DEBUG] Execution time: %e seconds" ./main print_dollar < input.txt 2>&1 | python3 script.py)
echo "$x"

if [ $? -eq 124 ]; then
    echo "TLE: Time Limit Exceeded"
    exit 0
fi

# Check for -d argument
if [[ "$1" == "-d" ]]; then
    echo "[Debug mode enabled]"
    python3 debugger.py
    exit 0
fi

