#!/bin/bash

# Quick Test Script for Pipex
# Run this for basic functionality testing

echo "🚀 Quick Pipex Test"

# Compile
echo "📦 Compiling..."
make

# Create a large file
shuf -n 500 /usr/share/dict/words | tr '\n' ' ' | fold -s -w 80 > lorem.txt

#for i in {1..200}; do shuf -n 8 /usr/share/dict/words | paste -sd' ' -; done > lorem.txt
#./pipex lorem.txt "cat" "wc -l" outfile
#cat outfile   # should print: 200

# Basic test
echo "🔧 Basic functionality test..."
echo "test content" > test_input.txt
./pipex test_input.txt "cat" "wc -l" test_output.txt
echo "Result: $(cat test_output.txt)"

# Error test
echo "⚠️  Error handling test..."
./pipex test_input.txt "nonexistent_command" "wc -l" test_output2.txt 2>/dev/null || echo "Error handled correctly"

# Cleanup
rm -f test_input.txt test_output.txt test_output2.txt

echo "✅ Quick test completed!"
