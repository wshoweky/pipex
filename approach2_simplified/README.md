# Simplified Approach2 Pipex 🚀

A clean, simplified version of the approach2 pipex implementation with **zero memory leaks** and **no complex PID tracking**.

## ✨ Key Improvements

### 🛡️ **Simplified Process Management**
- **❌ Removed**: Complex `pid_t *pids` array allocation
- **❌ Removed**: `waitpid()` with specific PID tracking
- **✅ Added**: Simple `int process_count` counter
- **✅ Added**: Clean `wait()` calls for all children

### 🧠 **Zero Memory Leaks**
```
Valgrind Results:
✅ HEAP SUMMARY: 0 bytes in 0 blocks in use at exit
✅ All heap blocks were freed -- no leaks are possible
✅ ERROR SUMMARY: 0 errors from 0 contexts
```

### 📐 **Clean Architecture**
- **Self-contained**: No external dependencies (no libft needed)
- **Modular design**: Clear separation of concerns
- **Simple functions**: Easy to understand and maintain
- **Robust error handling**: Proper error messages and cleanup

## 🏗️ **File Structure**

```
approach2_simplified/
├── include/
│   └── pipex.h              # Clean header with simplified prototypes
├── src/
│   ├── main.c               # Main logic and argument processing
│   ├── process.c            # Simplified process management
│   ├── execute.c            # Command execution
│   ├── utils.c              # Utility functions and error handling
│   ├── heredoc.c            # Heredoc functionality with built-in GNL
│   ├── string_utils.c       # String manipulation functions
│   └── ft_split.c           # String splitting functionality
├── Makefile                 # Simple build system
└── README.md                # This file
```

## 🔧 **Key Changes from Original Approach2**

### **Before (Complex & Leaky):**
```c
// Complex PID tracking
void process_command(char *cmd, char **envp, pid_t **pids, int *count) {
    // ... create process ...
    (*pids)[*count] = pid;  // Store PID in malloc'd array
    (*count)++;
}

void wait_for_process(pid_t *pids, int count) {
    for (int i = 0; i < count; i++)
        waitpid(pids[i], &status, 0);  // Wait for specific PIDs
}

// In main:
pid_t *pids = malloc(sizeof(pid_t) * max_pids);  // MEMORY LEAK!
```

### **After (Simple & Clean):**
```c
// Simple process counting
void process_command(char *cmd, char **envp, int *process_count) {
    // ... create process ...
    (*process_count)++;  // Just increment counter
}

void wait_for_all_processes(int count) {
    for (int i = 0; i < count; i++)
        wait(NULL);  // Simple wait for any child
}

// In main:
int process_count = 0;  // NO MALLOC NEEDED!
```

## 🚀 **Usage**

### **Compilation**
```bash
make                    # Build the project
make clean             # Clean object files
make test              # Run test suite
make valgrind          # Test for memory leaks
```

### **Basic Usage**
```bash
# Basic pipeline
./pipex input.txt "cmd1" "cmd2" output.txt

# Multi-command pipeline
./pipex input.txt "cmd1" "cmd2" "cmd3" output.txt

# Heredoc
./pipex here_doc LIMITER "cmd1" "cmd2" output.txt
```

### **Examples**
```bash
# Count lines containing "test"
./pipex input.txt "grep test" "wc -l" result.txt

# Sort numbers and get top 2
./pipex numbers.txt "sort -n" "head -2" "cat" sorted.txt

# Heredoc example
echo -e "hello\nworld\nEND" | ./pipex here_doc END "tr a-z A-Z" "wc -w" output.txt
```

## 🧪 **Test Results**

### **✅ Functionality Tests**
```bash
Test 1: Basic pipeline ✅
Test 2: Multi-command pipeline ✅  
Test 3: Heredoc ✅
```

### **✅ Memory Leak Tests**
```bash
Valgrind: All heap blocks were freed -- no leaks are possible ✅
```

## 🎯 **Why This Approach is Better**

### **1. Simplicity** 📐
- **No malloc/free** for process tracking
- **Simple counter** instead of complex arrays
- **Easy to understand** and maintain

### **2. Reliability** 🛡️
- **Zero memory leaks** (Valgrind verified)
- **No memory allocation errors** for PID tracking
- **Simpler error paths** with fewer failure points

### **3. Performance** ⚡
- **No malloc overhead** for process tracking
- **Faster execution** with simple wait() calls
- **Less memory usage** overall

### **4. Unix Philosophy** 🖥️
- **Trust the OS** to handle child processes
- **Simple wait()** works perfectly for pipelines
- **Less code** = fewer bugs

## 📊 **Comparison: Original vs Simplified**

| Feature | Original Approach2 | Simplified Approach2 |
|---------|-------------------|---------------------|
| **Memory Management** | ❌ malloc/free for pids | ✅ No dynamic allocation |
| **Process Tracking** | ❌ Complex PID arrays | ✅ Simple counter |
| **Memory Leaks** | ⚠️ Potential leaks | ✅ Zero leaks (verified) |
| **Code Complexity** | ❌ More complex | ✅ Simple and clean |
| **Error Handling** | ⚠️ More error paths | ✅ Fewer failure points |
| **Maintenance** | ❌ Harder to maintain | ✅ Easy to understand |

## 🔍 **Technical Details**

### **Process Management Strategy**
Instead of tracking specific PIDs, we:
1. **Count processes** as we create them
2. **Use simple wait()** to wait for any child
3. **Trust the OS** to handle process cleanup

### **Memory Management**
- **No dynamic allocation** for process tracking
- **Automatic cleanup** through process termination  
- **Static buffers** where appropriate (heredoc)
- **Proper string allocation** with immediate cleanup

### **Error Handling**
- **Consistent error messages** using `error_with_message()`
- **Proper cleanup** on all error paths
- **Early returns** to avoid complex nested logic

## 🎓 **Educational Value**

This implementation demonstrates:
- **Clean Unix programming** practices
- **Effective process management** without over-engineering
- **Memory safety** through simple design
- **Error handling** best practices

## 🏆 **Perfect for 42 School**

This version is ideal for 42 school because it:
- ✅ **Demonstrates understanding** of core concepts
- ✅ **Shows clean coding** practices
- ✅ **Has zero memory leaks** (evaluator-friendly)
- ✅ **Is easy to explain** during evaluation
- ✅ **Follows Unix philosophy** of simplicity

## 🤝 **Contributing**

This is an educational project. Feel free to study the code and learn from the simplification techniques used!

---

**Built with ❤️ for simple, robust Unix programming** 🚀

**Key Principle: "The best code is the code you don't have to write"** ✨
