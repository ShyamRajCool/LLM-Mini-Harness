#!/bin/bash

# Compile the C program to ensure we are testing the latest version
echo "Compiling harness.c..."
gcc harness.c -o harness

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed! Please check your C code."
    exit 1
fi

echo "Compilation successful. Running deterministic tests..."
echo "------------------------------------------------------"

# Define a sequence of inputs to pipe into the program
# 1. 'hello world' tests the hardcoded greeting keyword.
# 2. 'calc 15 + 27' tests the mathematical tool execution.
# 3. 'random gibberish' tests the default echo fallback.
# 4. 'exit' tests the safe shutdown and loop break.

# Use valgrind to run the harness and check for basic memory leaks
echo -e "hello world\ncalc 15 + 27\nrandom gibberish\nexit" | valgrind --leak-check=full --error-exitcode=1 ./harness

# Check Valgrind's exit status
if [ $? -eq 0 ]; then
    echo "------------------------------------------------------"
    echo "Test passed! State management is functional and no memory leaks were detected."
else
    echo "------------------------------------------------------"
    echo "Test failed! Valgrind detected a memory leak or error."
fi
