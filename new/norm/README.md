# PIPEX - Norm Compliant Version 🏆

## 📋 Overview

This is a **fully norm-compliant** implementation of the pipex project that:
- ✅ **Zero global variables** - Uses PID array approach
- ✅ **25 lines per function maximum**
- ✅ **5 functions per file maximum** 
- ✅ **Proper 42 header format**
- ✅ **No forbidden functions**
- ✅ **Clean memory management**

## 🏗️ Architecture

### **No-Globals Design**
Instead of global variables, we use:
```c
pid_t *pids = malloc(sizeof(pid_t) * max_commands);
int pid_count = 0;  // Local variable passed by reference
```

### **File Structure**
```
norm/
├── include/
│   └── pipex.h           # All prototypes and includes
├── src/
│   ├── main.c            # Main logic and setup
│   ├── process.c         # Process management
│   ├── execute.c         # Command execution and PATH resolution
│   ├── utils.c           # Basic utilities
│   ├── string_utils.c    # String manipulation functions
│   ├── ft_split.c        # String splitting function
│   └── get_next_line.c   # Line reading for heredoc
├── Makefile              # Build configuration
└── README.md             # This file
```

## 🔧 Build Instructions

```bash
# Build the project
make

# Run tests
make test

# Clean object files
make clean

# Clean everything
make fclean

# Rebuild from scratch
make re
```

## 🧪 Usage

### Basic Pipeline
```bash
./pipex infile "cmd1" "cmd2" outfile
# Equivalent to: < infile cmd1 | cmd2 > outfile
```

### Multi-Command Pipeline
```bash
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" outfile
# Equivalent to: < infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```

### Heredoc Mode
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
# Equivalent to: cmd1 << LIMITER | cmd2 >> outfile
```

## 🎯 Norm Compliance Features

### **Function Length** ≤ 25 lines
All functions are kept under 25 lines by:
- Breaking complex logic into helper functions
- Using clear, single-purpose functions
- Avoiding nested control structures

### **File Organization** ≤ 5 functions per file
- `main.c`: Main logic and setup functions
- `process.c`: Process creation and management
- `execute.c`: Command execution and PATH resolution
- `utils.c`: Basic utility functions
- `string_utils.c`: String manipulation
- `ft_split.c`: String splitting (complex function gets own file)
- `get_next_line.c`: Line reading for heredoc

### **No Global Variables**
Uses local variables and parameter passing:
```c
// Instead of: static int g_count = 0;
// We use:
void process_command(char *cmd, char **envp, pid_t **pids, int *count)
{
    // Store PID and increment counter
    (*pids)[*count] = pid;
    (*count)++;
}
```

### **Memory Management**
- All malloc'd memory is properly freed
- No memory leaks (tested with valgrind)
- Clean error handling with proper cleanup

### **Error Handling**
- Comprehensive error checking
- Proper exit codes (127 for command not found)
- Clear error messages

## 🏆 Key Advantages

1. **42-Legal**: Passes all norm checks
2. **Clean Architecture**: Well-organized, maintainable code
3. **No Dependencies**: Self-contained implementation
4. **Robust**: Handles edge cases and errors properly
5. **Efficient**: Parallel command execution
6. **Documented**: Clear code with good variable names

## 🧪 Test Results

All tests pass and match shell behavior:
- ✅ Basic 2-command pipeline
- ✅ Multi-command pipelines (3+ commands)
- ✅ Heredoc functionality
- ✅ Error handling for invalid files/commands
- ✅ Memory leak free

## 📚 Implementation Details

### **PID Management**
```c
// Allocate array for PIDs
pid_t *pids = malloc(sizeof(pid_t) * max_commands);
int pid_count = 0;

// Store each child PID
process_command(cmd, envp, &pids, &pid_count);

// Wait for all children at the end
wait_for_processes(pids, pid_count);
free(pids);
```

### **Heredoc Implementation**
Uses `get_next_line` to read user input until delimiter is found:
```c
while (get_next_line(STDIN_FILENO, &line) > 0) {
    if (matches_delimiter(line, limiter)) {
        free(line);
        break;
    }
    write_to_pipe(line);
    free(line);
}
```

### **PATH Resolution**
Searches through PATH environment variable:
```c
char **paths = get_paths(envp);  // Split PATH by ':'
// Try each path until executable found
char *full_path = try_each_path(cmd, paths);
```

This implementation is **production-ready** and **norm-compliant**! 🚀
