#!/bin/bash

# Test script for main pipex project
echo "🧪 Testing Main Pipex Project"
echo "=============================="

# Build the project
echo "📦 Building main project..."
make

# Test 1: Basic functionality
echo -e "\n1️⃣  Test 1: Basic pipe functionality"
echo "test line 1" > test_input.txt
echo "test line 2" >> test_input.txt
echo "test line 3" >> test_input.txt
echo "Input file content:"
cat test_input.txt
echo -e "\nRunning: ./pipex test_input.txt 'cat' 'wc -l' test_output.txt"
./pipex test_input.txt "cat" "wc -l" test_output.txt
echo "Output:"
cat test_output.txt
echo "Expected: 3"

# Test 2: Text filtering
echo -e "\n2️⃣  Test 2: Text filtering with grep"
./pipex test_input.txt "grep line" "wc -l" test_output2.txt
echo "Lines containing 'line':"
cat test_output2.txt
echo "Expected: 3"

# Test 3: Text transformation
echo -e "\n3️⃣  Test 3: Text transformation (uppercase)"
./pipex test_input.txt "tr '[:lower:]' '[:upper:]'" "cat" test_output3.txt
echo "Uppercase result:"
cat test_output3.txt

# Test 4: Data sorting
echo -e "\n4️⃣  Test 4: Data sorting"
echo "zebra" > test_sort.txt
echo "apple" >> test_sort.txt
echo "banana" >> test_sort.txt
echo "Original:"
cat test_sort.txt
echo -e "\nSorted:"
./pipex test_sort.txt "cat" "sort" test_output4.txt
cat test_output4.txt

# Test 5: Error handling - file not found
echo -e "\n5️⃣  Test 5: Error handling - file not found"
./pipex nonexistent.txt "cat" "wc -l" test_output5.txt 2>&1 || echo "Error handled correctly"

# Test 6: Error handling - command not found
echo -e "\n6️⃣  Test 6: Error handling - command not found"
./pipex test_input.txt "nonexistent_command" "wc -l" test_output6.txt 2>&1 || echo "Error handled correctly"

# Test 7: Usage error
echo -e "\n7️⃣  Test 7: Usage error (wrong number of arguments)"
./pipex 2>&1 || echo "Usage error handled correctly"

# Cleanup
echo -e "\n🧹 Cleaning up test files..."
rm -f test_input.txt test_output*.txt test_sort.txt

echo -e "\n🎉 Main project tests completed!"
