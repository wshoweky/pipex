#!/bin/bash

# Pipex Demo Script
# Shows the most common and useful use cases

echo "🎬 Pipex Demo - Common Use Cases"
echo "================================"

# Demo 1: Basic file processing
echo -e "\n1️⃣  Demo 1: Count lines in a file"
echo "Creating sample file..."
echo "Line 1" > demo1.txt
echo "Line 2" >> demo1.txt
echo "Line 3" >> demo1.txt
echo "File content:"
cat demo1.txt
echo -e "\nCounting lines:"
./pipex demo1.txt "cat" "wc -l" demo1_result.txt
echo "Result: $(cat demo1_result.txt) lines"

# Demo 2: Text filtering
echo -e "\n2️⃣  Demo 2: Filter lines containing 'Line'"
./pipex demo1.txt "grep Line" "wc -l" demo2_result.txt
echo "Lines containing 'Line': $(cat demo2_result.txt)"

# Demo 3: Text transformation
echo -e "\n3️⃣  Demo 3: Convert text to uppercase"
./pipex demo1.txt "tr '[:lower:]' '[:upper:]'" "cat" demo3_result.txt
echo "Uppercase result:"
cat demo3_result.txt

# Demo 4: Data sorting
echo -e "\n4️⃣  Demo 4: Sort data"
echo "zebra" > demo4.txt
echo "apple" >> demo4.txt
echo "banana" >> demo4.txt
echo "Original data:"
cat demo4.txt
echo -e "\nSorted data:"
./pipex demo4.txt "cat" "sort" demo4_result.txt
cat demo4_result.txt

# Demo 5: Log analysis
echo -e "\n5️⃣  Demo 5: Analyze log file"
cat > demo5.log << EOF
2024-01-01 INFO: System started
2024-01-01 ERROR: Connection failed
2024-01-01 INFO: Retrying connection
2024-01-01 ERROR: Timeout occurred
EOF
echo "Log file:"
cat demo5.log
echo -e "\nCounting errors:"
./pipex demo5.log "grep ERROR" "wc -l" demo5_result.txt
echo "Error count: $(cat demo5_result.txt)"

# Demo 6: Data extraction
echo -e "\n6️⃣  Demo 6: Extract specific data"
cat > demo6.txt << EOF
John|Doe|25|Engineer
Jane|Smith|30|Designer
Bob|Johnson|35|Manager
EOF
echo "Data file:"
cat demo6.txt
echo -e "\nExtracting names (first column):"
./pipex demo6.txt "cut -d'|' -f1" "cat" demo6_result.txt
cat demo6_result.txt

# Demo 7: Text search and replace
echo -e "\n7️⃣  Demo 7: Search and replace"
echo "Hello world" > demo7.txt
echo "Welcome to the world" >> demo7.txt
echo "Original text:"
cat demo7.txt
echo -e "\nAfter replacing 'world' with 'UNIVERSE':"
./pipex demo7.txt "sed s/world/UNIVERSE/g" "cat" demo7_result.txt
cat demo7_result.txt

# Demo 8: Performance test
echo -e "\n8️⃣  Demo 8: Performance test (1000 lines)"
echo "Generating 1000 lines..."
for i in {1..1000}; do
    echo "Line $i" >> demo8.txt
done
echo "Processing large file..."
./pipex demo8.txt "wc -l" "cat" demo8_result.txt
echo "Total lines: $(cat demo8_result.txt)"

# Demo 9: Error handling
echo -e "\n9️⃣  Demo 9: Error handling"
echo "Testing with non-existent file:"
./pipex nonexistent.txt "cat" "wc -l" demo9_result.txt 2>/dev/null || echo "✅ Error handled correctly"

# Demo 10: Complex command - Find unique words
echo -e "\n🔟  Demo 10: Complex command - Find unique words"
cat > demo10.txt << EOF
apple
banana
apple
cherry
banana
cherry
date
elderberry
EOF
echo "Original text:"
cat demo10.txt
echo -e "\nUnique words (sorted):"
./pipex demo10.txt "sort" "uniq" demo10_result.txt
cat demo10_result.txt

# Cleanup
echo -e "\n🧹 Cleaning up demo files..."
rm -f demo*.txt demo*.log demo*_result.txt

echo -e "\n🎉 Demo completed!"
echo "📊 Demo Summary:"
echo "- ✅ Basic file processing"
echo "- ✅ Text filtering and transformation"
echo "- ✅ Data sorting and extraction"
echo "- ✅ Log analysis"
echo "- ✅ Search and replace"
echo "- ✅ Performance testing"
echo "- ✅ Error handling"
echo "- ✅ Complex command chaining"
echo "- ✅ Data formatting"

echo -e "\n💡 These demos show the most common use cases for pipex!"
echo "🚀 Try running: ./useful_test_cases.sh for more comprehensive testing"
