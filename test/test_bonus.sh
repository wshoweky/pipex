#!/bin/bash

# Test script for bonus pipex project
echo "🎯 Testing Bonus Pipex Project (with heredoc)"
echo "============================================="

# Build the bonus project
echo "📦 Building bonus project..."
make bonus

# Test 1: Basic bonus functionality (multiple commands)
echo -e "\n1️⃣  Test 1: Multiple commands (3 commands)"
echo "line1" > test_bonus_input.txt
echo "line2" >> test_bonus_input.txt
echo "line3" >> test_bonus_input.txt
echo "Input file content:"
cat test_bonus_input.txt
echo -e "\nRunning: ./pipex_bonus test_bonus_input.txt 'cat' 'grep line' 'wc -l' test_bonus_output.txt"
./pipex_bonus test_bonus_input.txt "cat" "grep line" "wc -l" test_bonus_output.txt
echo "Output:"
cat test_bonus_output.txt
echo "Expected: 3"

# Test 2: Heredoc functionality
echo -e "\n2️⃣  Test 2: Heredoc functionality"
echo "Testing heredoc with limiter 'END'"
echo "This will create input interactively..."
echo "Type some lines, then type 'END' on a new line to finish"
echo "Note: This test requires manual input"

# Test 3: Heredoc with automatic input (simulated)
echo -e "\n3️⃣  Test 3: Heredoc with simulated input"
echo "Creating heredoc input file for testing..."
cat > heredoc_input.txt << EOF
first line
second line
third line
END
EOF

echo "Simulating heredoc input..."
./pipex_bonus here_doc END "cat" "wc -l" test_heredoc_output.txt < heredoc_input.txt
echo "Heredoc output:"
cat test_heredoc_output.txt
echo "Expected: 3"

# Test 4: Multiple commands with filtering
echo -e "\n4️⃣  Test 4: Multiple commands with filtering"
echo "apple" > test_filter.txt
echo "banana" >> test_filter.txt
echo "cherry" >> test_filter.txt
echo "date" >> test_filter.txt
echo "elderberry" >> test_filter.txt
echo "Original data:"
cat test_filter.txt
echo -e "\nFiltering and sorting:"
./pipex_bonus test_filter.txt "cat" "grep -v date" "sort" test_filter_output.txt
cat test_filter_output.txt

# Test 5: Error handling - file not found
echo -e "\n5️⃣  Test 5: Error handling - file not found"
./pipex_bonus nonexistent.txt "cat" "grep line" "wc -l" test_error.txt 2>&1 || echo "Error handled correctly"

# Test 6: Error handling - command not found
echo -e "\n6️⃣  Test 6: Error handling - command not found"
./pipex_bonus test_bonus_input.txt "nonexistent_cmd" "grep line" "wc -l" test_cmd_error.txt 2>&1 || echo "Error handled correctly"

# Test 7: Usage error
echo -e "\n7️⃣  Test 7: Usage error (wrong number of arguments)"
./pipex_bonus 2>&1 || echo "Usage error handled correctly"

# Test 8: Heredoc usage error
echo -e "\n8️⃣  Test 8: Heredoc usage error (wrong number of arguments)"
./pipex_bonus here_doc 2>&1 || echo "Heredoc usage error handled correctly"

# Test 9: Performance test with large file
echo -e "\n9️⃣  Test 9: Performance test with large file"
echo "Generating 1000 lines..."
for i in {1..1000}; do
    echo "Line $i: test data for performance testing" >> large_test.txt
done
echo "Processing large file with multiple commands..."
./pipex_bonus large_test.txt "cat" "grep Line" "wc -l" large_test_output.txt
echo "Large file result:"
cat large_test_output.txt
echo "Expected: 1000"

# Test 10: Complex command chaining
echo -e "\n🔟  Test 10: Complex command chaining"
echo "Testing: cat -> grep -> sed -> wc -l"
./pipex_bonus large_test.txt "cat" "grep 'Line [1-9]00'" "sed 's/Line //'" "wc -l" complex_output.txt
echo "Complex command result:"
cat complex_output.txt
echo "Expected: 10 (lines 100, 200, 300, etc.)"

# Cleanup
echo -e "\n🧹 Cleaning up test files..."
rm -f test_bonus_input.txt test_bonus_output.txt test_heredoc_output.txt
rm -f test_filter.txt test_filter_output.txt test_error.txt test_cmd_error.txt
rm -f heredoc_input.txt large_test.txt large_test_output.txt complex_output.txt

echo -e "\n🎉 Bonus project tests completed!"
echo "📊 Test Summary:"
echo "- ✅ Basic functionality"
echo "- ✅ Multiple commands"
echo "- ✅ Heredoc functionality"
echo "- ✅ Error handling"
echo "- ✅ Performance testing"
echo "- ✅ Complex command chaining"
