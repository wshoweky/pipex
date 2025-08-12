# pipex

A Unix pipe implementation in C that mimics the behavior of the shell pipe operator `|`. This project includes both a main implementation and a bonus version with heredoc support and multiple command chaining.

## Description

### Main Project
The main project implements a program that takes four arguments:
- `file1`: input file
- `cmd1`: first command
- `cmd2`: second command  
- `file2`: output file

The program executes: `< file1 cmd1 | cmd2 > file2`

### Bonus Project
The bonus project extends the functionality with:
- **Multiple Commands**: Support for 3 or more commands in a pipeline
- **Heredoc**: Interactive input mode using `here_doc` limiter
- **Enhanced Error Handling**: Better error messages and status codes

## Usage

### Main Project
```bash
./pipex file1 cmd1 cmd2 file2
```

### Bonus Project
```bash
# Multiple commands
./pipex_bonus file1 cmd1 cmd2 cmd3 ... outfile

# Heredoc mode
./pipex_bonus here_doc LIMITER cmd1 cmd2 ... outfile
```

## Examples

### Main Project
```bash
# Count lines in a file
./pipex input.txt "cat" "wc -l" output.txt

# Search for lines containing "test" and count them
./pipex input.txt "grep test" "wc -l" output.txt

# Replace text and sort
./pipex input.txt "sed 's/old/new/'" "sort" output.txt
```

### Bonus Project
```bash
# Multiple commands: cat -> grep -> wc -l
./pipex_bonus input.txt "cat" "grep line" "wc -l" output.txt

# Heredoc with multiple commands
./pipex_bonus here_doc END "cat" "grep -v date" "sort" output.txt
# Then type lines and end with "END"
```

## Building

```bash
# Build main project
make

# Build bonus project
make bonus

# Build both
make && make bonus

# Clean
make clean

# Full clean
make fclean
```

## Testing

All test scripts are located in the `test/` directory.

### Quick Tests
```bash
# Test main project
./test/test_main.sh

# Test bonus project
./test/test_bonus.sh

# Run all tests
./test/run_all_tests.sh
```

### Test Directory Structure
```
test/
├── test_main.sh          # Main project tests
├── test_bonus.sh         # Bonus project tests
└── run_all_tests.sh      # Complete test suite
```

## Features

### Main Project
- ✅ Basic pipe functionality (2 commands)
- ✅ Proper error handling
- ✅ Memory leak prevention
- ✅ Robust command execution
- ✅ File permission handling
- ✅ Environment variable support

### Bonus Project
- ✅ Multiple command support (3+ commands)
- ✅ Heredoc functionality
- ✅ Enhanced error handling
- ✅ Process management
- ✅ All main project features

## Error Handling

Both projects handle various error conditions:
- Invalid number of arguments
- File not found
- Command not found
- Permission denied
- Memory allocation failures
- Pipe creation failures
- Fork failures

## Project Structure

```
pipex/
├── src/                  # Main project source files
│   ├── pipex.c          # Main program logic
│   ├── pipex.h          # Main project header
│   └── utils.c          # Utility functions
├── src_bonus/           # Bonus project source files
│   ├── pipex_bonus.c    # Bonus main program
│   ├── pipex_bonus.h    # Bonus project header
│   ├── heredoc.c        # Heredoc implementation
│   ├── process.c        # Process management
│   └── utils_bonus.c    # Bonus utility functions
├── libft/               # Custom library functions
├── test/                # Test scripts
└── Makefile             # Build system
```

## Dependencies

- GCC compiler
- Standard C libraries
- Unix/Linux environment
- Custom libft library (included)