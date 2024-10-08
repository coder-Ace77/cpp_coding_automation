#!/bin/bash

g++ main.cpp -o main
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

./main < input.txt > output.txt
sed -i 's|// cout<<\"\$\"<<endl;|cout<<\"\$\"<<endl;|' main.cpp

g++ main.cpp -o main
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

./main < input.txt > outputx.txt

if [ $? -ne 0 ]; then
    echo "Execution failed"
    exit 1
fi

python3 script.py

sed -i 's|cout<<\"\$\"<<endl;|// cout<<\"\$\"<<endl;|' main.cpp
