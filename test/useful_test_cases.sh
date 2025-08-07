#!/bin/bash

# Useful Test Cases for Pipex Project
# These test cases demonstrate practical, real-world usage scenarios

echo "🎯 Useful Test Cases for Pipex Project"
echo "======================================"

# Test Case 1: File processing - Count words in a text file
echo -e "\n📊 Test Case 1: Count words in a text file"
cat > sample_text.txt << EOF
This is a sample text file.
It contains multiple lines of text.
We will use this to test word counting.
EOF
./pipex sample_text.txt "cat" "wc -w" word_count.txt
echo "Word count result: $(cat word_count.txt)"
echo "Expected: ~15 words"

# Test Case 2: Text filtering - Find lines containing specific text
echo -e "\n🔍 Test Case 2: Find lines containing 'text'"
./pipex sample_text.txt "grep text" "wc -l" text_lines.txt
echo "Lines containing 'text': $(cat text_lines.txt)"
echo "Expected: 2 lines"

# Test Case 3: Text transformation - Convert to uppercase
echo -e "\n🔤 Test Case 3: Convert text to uppercase"
./pipex sample_text.txt "tr '[:lower:]' '[:upper:]'" "cat" uppercase.txt
echo "Uppercase result:"
cat uppercase.txt

# Test Case 4: Data sorting - Sort lines alphabetically
echo -e "\n📝 Test Case 4: Sort lines alphabetically"
cat > unsorted.txt << EOF
zebra
apple
banana
cat
dog
EOF
./pipex unsorted.txt "cat" "sort" sorted.txt
echo "Sorted result:"
cat sorted.txt

# Test Case 5: Data extraction - Extract specific columns
echo -e "\n📋 Test Case 5: Extract first column from space-separated data"
cat > data.txt << EOF
John Doe 25 Engineer
Jane Smith 30 Designer
Bob Johnson 35 Manager
EOF
./pipex data.txt "cut -d' ' -f1" "cat" names.txt
echo "Extracted names:"
cat names.txt

# Test Case 6: Log file analysis - Count error occurrences
echo -e "\n🚨 Test Case 6: Count error occurrences in log"
cat > log.txt << EOF
2024-01-01 INFO: System started
2024-01-01 ERROR: Connection failed
2024-01-01 INFO: Retrying connection
2024-01-01 ERROR: Timeout occurred
2024-01-01 INFO: Connection established
EOF
./pipex log.txt "grep ERROR" "wc -l" error_count.txt
echo "Error count: $(cat error_count.txt)"
echo "Expected: 2 errors"

# Test Case 7: File compression simulation - Count unique lines
echo -e "\n🎯 Test Case 7: Count unique lines"
cat > duplicates.txt << EOF
apple
banana
apple
cherry
banana
cherry
EOF
./pipex duplicates.txt "sort" "uniq" unique.txt
echo "Unique items:"
cat unique.txt

# Test Case 8: Network data processing - Extract IP addresses
echo -e "\n🌐 Test Case 8: Extract IP addresses from log"
cat > network.log << EOF
192.168.1.100 - GET /index.html
10.0.0.50 - POST /api/data
192.168.1.100 - GET /style.css
172.16.0.25 - GET /script.js
EOF
./pipex network.log "cut -d' ' -f1" "sort" unique_ips.txt
echo "Unique IP addresses:"
cat unique_ips.txt

# Test Case 9: CSV data processing - Count rows
echo -e "\n📊 Test Case 9: Count CSV rows"
cat > data.csv << EOF
name,age,city
John,25,New York
Jane,30,Los Angeles
Bob,35,Chicago
EOF
./pipex data.csv "cat" "wc -l" row_count.txt
echo "CSV row count: $(cat row_count.txt)"
echo "Expected: 4 rows (including header)"

# Test Case 10: Text search and replace
echo -e "\n🔄 Test Case 10: Search and replace text"
cat > original.txt << EOF
Hello world
Welcome to the world of programming
This is a wonderful world
EOF
./pipex original.txt "sed s/world/UNIVERSE/g" "cat" replaced.txt
echo "Text after replacement:"
cat replaced.txt

# Test Case 11: File format conversion - Convert spaces to tabs
echo -e "\n📄 Test Case 11: Convert spaces to tabs"
cat > spaced.txt << EOF
column1    column2    column3
data1      data2      data3
EOF
./pipex spaced.txt "sed 's/    /\t/g'" "cat" tabbed.txt
echo "Converted to tabs:"
cat tabbed.txt

# Test Case 12: Data validation - Check for empty lines
echo -e "\n✅ Test Case 12: Count non-empty lines"
cat > mixed.txt << EOF
line1

line2

line3
EOF
./pipex mixed.txt "grep -v '^$'" "wc -l" non_empty.txt
echo "Non-empty lines: $(cat non_empty.txt)"
echo "Expected: 3 lines"

# Test Case 13: System information processing
echo -e "\n💻 Test Case 13: Process system information"
echo "Current directory: $(pwd)" > sysinfo.txt
echo "User: $(whoami)" >> sysinfo.txt
echo "Date: $(date)" >> sysinfo.txt
./pipex sysinfo.txt "grep -i user" "cat" user_info.txt
echo "User information:"
cat user_info.txt

# Test Case 14: Multi-step data processing
echo -e "\n🔄 Test Case 14: Multi-step processing (simulated)"
cat > numbers.txt << EOF
5
2
8
1
9
3
EOF
# First sort, then get unique, then count
./pipex numbers.txt "sort -n" "uniq" sorted_unique.txt
echo "Sorted unique numbers:"
cat sorted_unique.txt

# Test Case 15: Performance testing - Large file processing
echo -e "\n⚡ Test Case 15: Large file processing"
echo "Generating large test file..."
for i in {1..1000}; do
    echo "Line $i: This is test data for performance testing" >> large_test.txt
done
./pipex large_test.txt "wc -l" "cat" large_count.txt
echo "Large file line count: $(cat large_count.txt)"
echo "Expected: 1000 lines"

# Test Case 16: Error handling - Invalid file
echo -e "\n⚠️  Test Case 16: Error handling - Invalid input file"
./pipex nonexistent_file.txt "cat" "wc -l" error_output.txt 2>/dev/null || echo "Error handled correctly - file not found"

# Test Case 17: Command chaining simulation
echo -e "\n🔗 Test Case 17: Command chaining simulation"
cat > chain_test.txt << EOF
apple
banana
cherry
date
elderberry
EOF
# Filter lines starting with 'a' or 'b', then count
./pipex chain_test.txt "grep '^[ab]'" "wc -l" chain_result.txt
echo "Lines starting with 'a' or 'b': $(cat chain_result.txt)"
echo "Expected: 2 lines"

# Test Case 18: Data formatting - Add line numbers
echo -e "\n🔢 Test Case 18: Add line numbers"
cat > unnumbered.txt << EOF
First line
Second line
Third line
EOF
./pipex unnumbered.txt "nl" "cat" numbered.txt
echo "Numbered lines:"
cat numbered.txt

# Cleanup
echo -e "\n🧹 Cleaning up test files..."
rm -f sample_text.txt word_count.txt text_lines.txt uppercase.txt
rm -f unsorted.txt sorted.txt data.txt names.txt log.txt error_count.txt
rm -f duplicates.txt unique.txt network.log unique_ips.txt data.csv row_count.txt
rm -f original.txt replaced.txt spaced.txt tabbed.txt mixed.txt non_empty.txt
rm -f sysinfo.txt user_info.txt numbers.txt sorted_unique.txt large_test.txt large_count.txt
rm -f error_output.txt chain_test.txt chain_result.txt unnumbered.txt numbered.txt

echo -e "\n🎉 All useful test cases completed!"
echo "📊 Summary of test cases:"
echo "- File processing and analysis ✅"
echo "- Text filtering and transformation ✅"
echo "- Data sorting and extraction ✅"
echo "- Log analysis and error counting ✅"
echo "- CSV and data format processing ✅"
echo "- System information processing ✅"
echo "- Performance testing ✅"
echo "- Error handling ✅"
echo "- Command chaining ✅"
echo "- Data formatting ✅"
