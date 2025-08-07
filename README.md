# pipex

A Unix pipe implementation in C that mimics the behavior of the shell pipe operator `|`.

## Description

This project implements a program that takes four arguments:
- `file1`: input file
- `cmd1`: first command
- `cmd2`: second command  
- `file2`: output file

The program executes: `< file1 cmd1 | cmd2 > file2`

## Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

## Examples

```bash
# Count lines in a file
./pipex input.txt "cat" "wc -l" output.txt

# Search for lines containing "test" and count them
./pipex input.txt "grep test" "wc -l" output.txt

# Replace text and sort
./pipex input.txt "sed 's/old/new/'" "sort" output.txt
```

## Building

```bash
make
```

## Testing

All test scripts are located in the `test/` directory.

### Quick Test
Run the quick test script for basic functionality:
```bash
./test/quick_test.sh
```

### Demo
Run the demo script to see common use cases:
```bash
./test/demo.sh
```

### Full Test Suite
Run the comprehensive test suite:
```bash
./test/test_commands.sh
```

### Useful Test Cases
Run practical, real-world test cases:
```bash
./test/useful_test_cases.sh
```

### Test Directory Structure
```
test/
├── quick_test.sh          # Quick basic functionality test
├── demo.sh                # Common use cases demonstration
├── test_commands.sh       # Comprehensive test suite
└── useful_test_cases.sh   # Real-world practical test cases
```

The test suite includes:
- ✅ Compilation testing
- ✅ Basic functionality testing
- ✅ Error handling testing
- ✅ Complex command testing
- ✅ Edge case testing
- ✅ Real-world scenarios
- ✅ Performance testing

## Features

- ✅ Proper error handling
- ✅ Memory leak prevention
- ✅ Robust command execution
- ✅ File permission handling
- ✅ Environment variable support
- ✅ Clean build system

## Error Handling

The program handles various error conditions:
- Invalid number of arguments
- File not found
- Command not found
- Permission denied
- Memory allocation failures