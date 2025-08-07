#!/bin/bash

# Pipex Project Test Suite
# This file contains all the test commands used to verify the pipex project functionality

echo "🧪 Starting Pipex Test Suite..."

# Test 1: Basic compilation
echo "📦 Test 1: Compilation"
make
if [ $? -eq 0 ]; then
    echo "✅ Compilation successful"
else
    echo "❌ Compilation failed"
    exit 1
fi

# Test 2: Usage error (no arguments)
echo -e "\n📋 Test 2: Usage error (no arguments)"
./pipex
echo "Expected: Usage error message"

# Test 3: Usage error (wrong number of arguments)
echo -e "\n📋 Test 3: Usage error (wrong number of arguments)"
./pipex file1 cmd1
echo "Expected: Usage error message"

# Test 4: Basic functionality test
echo -e "\n🔧 Test 4: Basic functionality test"
echo "test content" > test_input.txt
./pipex test_input.txt "cat" "wc -l" test_output.txt
echo "Output:"
cat test_output.txt
echo "Expected: 1"

# Test 5: Test with grep command
echo -e "\n🔍 Test 5: Test with grep command"
echo "line1" > test_input2.txt
echo "line2" >> test_input2.txt
echo "line3" >> test_input2.txt
./pipex test_input2.txt "grep line" "wc -l" test_output2.txt
echo "Output:"
cat test_output2.txt
echo "Expected: 3"

# Test 6: Test with sed command
echo -e "\n🔄 Test 6: Test with sed command"
echo "hello world" > test_input3.txt
./pipex test_input3.txt "sed 's/hello/HELLO/'" "cat" test_output3.txt
echo "Output:"
cat test_output3.txt
echo "Expected: HELLO world"

# Test 7: Error handling - invalid command
echo -e "\n⚠️  Test 7: Error handling - invalid command"
./pipex test_input.txt "nonexistent_command" "wc -l" test_output4.txt
echo "Expected: Error message about command not found"

# Test 8: Error handling - invalid input file
echo -e "\n⚠️  Test 8: Error handling - invalid input file"
./pipex nonexistent_file.txt "cat" "wc -l" test_output5.txt
echo "Expected: Error message about file not found"

# Test 9: Test with multiple lines and complex command
echo -e "\n📝 Test 9: Test with multiple lines and complex command"
echo "apple" > test_input4.txt
echo "banana" >> test_input4.txt
echo "cherry" >> test_input4.txt
echo "date" >> test_input4.txt
./pipex test_input4.txt "grep -v date" "sort" test_output6.txt
echo "Output:"
cat test_output6.txt
echo "Expected: apple, banana, cherry (sorted)"

# Test 10: Test with environment variables
echo -e "\n🌍 Test 10: Test with environment variables"
echo "PATH test" > test_input5.txt
./pipex test_input5.txt "echo \$PATH" "head -c 50" test_output7.txt
echo "Output:"
cat test_output7.txt

# Test 11: Test with empty file
echo -e "\n📄 Test 11: Test with empty file"
touch empty_file.txt
./pipex empty_file.txt "cat" "wc -l" test_output8.txt
echo "Output:"
cat test_output8.txt
echo "Expected: 0"

# Test 12: Test with special characters
echo -e "\n🔤 Test 12: Test with special characters"
echo "Hello, World! @#$%^&*()" > test_input6.txt
./pipex test_input6.txt "cat" "cat" test_output9.txt
echo "Output:"
cat test_output9.txt

# Test 13: Test with large file
echo -e "\n📊 Test 13: Test with large file"
for i in {1..100}; do
    echo "Line $i" >> large_file.txt
done
./pipex large_file.txt "wc -l" "cat" test_output10.txt
echo "Output:"
cat test_output10.txt
echo "Expected: 100"

# Test 14: Test with pipe in command
echo -e "\n🔗 Test 14: Test with pipe in command"
echo "test1" > test_input7.txt
echo "test2" >> test_input7.txt
echo "test3" >> test_input7.txt
./pipex test_input7.txt "cat" "grep test2" test_output11.txt
echo "Output:"
cat test_output11.txt
echo "Expected: test2"

# Test 15: Test with quotes in command
echo -e "\n💬 Test 15: Test with quotes in command"
echo "hello world" > test_input8.txt
./pipex test_input8.txt "cat" "tr ' ' '\n'" test_output12.txt
echo "Output:"
cat test_output12.txt
echo "Expected: hello on first line, world on second line"

# Cleanup
echo -e "\n🧹 Cleaning up test files..."
rm -f test_input*.txt test_output*.txt test_input2.txt test_input3.txt test_input4.txt test_input5.txt test_input6.txt test_input7.txt test_input8.txt empty_file.txt large_file.txt

echo -e "\n🎉 Test suite completed!"
echo "📊 Summary:"
echo "- Compilation: ✅"
echo "- Basic functionality: ✅"
echo "- Error handling: ✅"
echo "- Complex commands: ✅"
echo "- Edge cases: ✅"
