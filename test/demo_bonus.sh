#!/bin/bash

# Demo script for bonus pipex features
echo "🎬 Bonus Pipex Features Demo"
echo "============================"

# Build bonus project
echo "📦 Building bonus project..."
make bonus

echo -e "\n🚀 Demo 1: Multiple Commands (3 commands)"
echo "Creating test data..."
echo "apple" > demo_input.txt
echo "banana" >> demo_input.txt
echo "cherry" >> demo_input.txt
echo "date" >> demo_input.txt
echo "elderberry" >> demo_input.txt

echo "Input data:"
cat demo_input.txt

echo -e "\nRunning: ./pipex_bonus demo_input.txt 'cat' 'grep -v date' 'sort' demo_output.txt"
./pipex_bonus demo_input.txt "cat" "grep -v date" "sort" demo_output.txt

echo "Result (filtered and sorted):"
cat demo_output.txt

echo -e "\n🚀 Demo 2: Heredoc Functionality"
echo "Creating heredoc input for testing..."
cat > heredoc_demo.txt << EOF
first line of text
second line of text
third line of text
END
EOF

echo "Simulating heredoc input..."
./pipex_bonus here_doc END "cat" "wc -l" heredoc_output.txt < heredoc_demo.txt

echo "Heredoc result (line count):"
cat heredoc_output.txt

echo -e "\n🚀 Demo 3: Complex Pipeline"
echo "Testing: cat -> grep -> sed -> wc -l"
echo "apple 1" > complex_input.txt
echo "banana 2" >> complex_input.txt
echo "cherry 3" >> complex_input.txt
echo "date 4" >> complex_input.txt
echo "elderberry 5" >> complex_input.txt

echo "Input data:"
cat complex_input.txt

echo -e "\nRunning complex pipeline..."
./pipex_bonus complex_input.txt "cat" "grep -v date" "sed 's/ [0-9]//'" "wc -l" complex_output.txt

echo "Complex pipeline result:"
cat complex_output.txt

echo -e "\n🚀 Demo 4: Performance Test"
echo "Generating 500 lines..."
for i in {1..500}; do
    echo "Line $i: test data" >> perf_input.txt
done

echo "Processing with multiple commands..."
./pipex_bonus perf_input.txt "cat" "grep 'Line [1-9]00'" "wc -l" perf_output.txt

echo "Performance test result:"
cat perf_output.txt
echo "Expected: 5 (lines 100, 200, 300, 400, 500)"

# Cleanup
echo -e "\n🧹 Cleaning up demo files..."
rm -f demo_input.txt demo_output.txt heredoc_demo.txt heredoc_output.txt
rm -f complex_input.txt complex_output.txt perf_input.txt perf_output.txt

echo -e "\n🎉 Bonus features demo completed!"
echo "📊 Demo Summary:"
echo "- ✅ Multiple command support (3+ commands)"
echo "- ✅ Heredoc functionality"
echo "- ✅ Complex command chaining"
echo "- ✅ Performance with large files"
echo ""
echo "💡 Try these commands manually:"
echo "  ./pipex_bonus input.txt 'cat' 'grep pattern' 'wc -l' output.txt"
echo "  ./pipex_bonus here_doc LIMITER 'cat' 'sort' output.txt"
