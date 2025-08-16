#!/bin/bash

# Create a test command in the current directory
echo '#!/bin/bash
echo "This is a test command in the current directory"' > ./testcmd
chmod +x ./testcmd

# Create a test input file
echo "Test input" > test_input.txt

# Test with the command in current directory
echo "Testing with command in current directory:"
./pipex test_input.txt "./testcmd" "wc -l" output.txt
cat output.txt
echo

# Clean up
rm -f ./testcmd test_input.txt output.txt
echo "Test completed"
