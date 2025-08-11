# 🔄 Smart Refactoring: Combining Duplicate Functions

## 🎯 **The Problem You Identified**

You correctly noticed that `process_pipeline()` and `process_heredoc()` are almost identical:

### **Before (Duplicate Code):**
```c
static void	process_pipeline(int argc, char **argv, char **envp)
{
    pid_t *pids;
    int pid_count, i, max_pids;
    
    max_pids = argc - 3;        // ← Only difference 1
    pids = malloc(sizeof(pid_t) * max_pids);
    if (!pids) error_exit();
    pid_count = 0;
    // No heredoc setup             ← Only difference 2
    i = 2;                      // ← Only difference 3
    while (i < argc - 2) {
        process_command(argv[i], envp, &pids, &pid_count);
        i++;
    }
    setup_output_file(argv[argc - 1], 1);  // ← Only difference 4
    wait_for_processes(pids, pid_count);
    free(pids);
    execute_command(argv[argc - 2], envp);
}

static void	process_heredoc(int argc, char **argv, char **envp)
{
    pid_t *pids;
    int pid_count, i, max_pids;
    
    max_pids = argc - 4;        // ← Only difference 1
    pids = malloc(sizeof(pid_t) * max_pids);
    if (!pids) error_exit();
    pid_count = 0;
    handle_heredoc(argv[2], argc);  // ← Only difference 2
    i = 3;                      // ← Only difference 3
    while (i < argc - 2) {
        process_command(argv[i], envp, &pids, &pid_count);
        i++;
    }
    setup_output_file(argv[argc - 1], 0);  // ← Only difference 4
    wait_for_processes(pids, pid_count);
    free(pids);
    execute_command(argv[argc - 2], envp);
}
```

## ✅ **After (Combined & Elegant):**

```c
static void	process_commands(int argc, char **argv, char **envp, int is_heredoc)
{
    pid_t *pids;
    int pid_count, i, max_pids;
    
    max_pids = argc - (3 + is_heredoc);    // Smart calculation!
    pids = malloc(sizeof(pid_t) * max_pids);
    if (!pids) error_exit();
    pid_count = 0;
    
    if (is_heredoc)                        // Conditional setup
        handle_heredoc(argv[2], argc);
        
    i = 2 + is_heredoc;                    // Dynamic start position
    while (i < argc - 2) {
        process_command(argv[i], envp, &pids, &pid_count);
        i++;
    }
    setup_output_file(argv[argc - 1], !is_heredoc);  // Smart mode
    wait_for_processes(pids, pid_count);
    free(pids);
    execute_command(argv[argc - 2], envp);
}
```

---

## 🧮 **How the Math Works**

### **Smart Parameter Calculation:**

| Mode | is_heredoc | max_pids formula | Result |
|------|------------|------------------|--------|
| **Regular** | 0 | `argc - (3 + 0) = argc - 3` | ✅ Correct |
| **Heredoc** | 1 | `argc - (3 + 1) = argc - 4` | ✅ Correct |

### **Dynamic Start Position:**

| Mode | is_heredoc | i = 2 + is_heredoc | Starts from |
|------|------------|-------------------|-------------|
| **Regular** | 0 | `2 + 0 = 2` | `argv[2]` (first command) |
| **Heredoc** | 1 | `2 + 1 = 3` | `argv[3]` (first command after limiter) |

### **Output Mode Selection:**

| Mode | is_heredoc | !is_heredoc | setup_output_file mode |
|------|------------|-------------|----------------------|
| **Regular** | 0 | 1 | Truncate mode ✅ |
| **Heredoc** | 1 | 0 | Append mode ✅ |

---

## 🏆 **Benefits of This Refactoring**

### **1. Norm Compliance ✅**
- **Function count reduced:** From 5 to 4 functions in main.c
- **Line count:** Combined function is ~25 lines (within norm)
- **No global variables:** Still maintains clean architecture

### **2. Code Quality ✅**
- **DRY Principle:** No duplicate code
- **Maintainability:** Single function to maintain
- **Readability:** Clear parameter indicates mode
- **Flexibility:** Easy to add new modes if needed

### **3. Performance ✅**
- **Same performance:** No overhead added
- **Memory usage:** Identical allocation patterns
- **Execution path:** Same logic flow

---

## 🔍 **Usage Comparison**

### **Before:**
```c
if (ft_strncmp(argv[1], "here_doc", 8) == 0) {
    process_heredoc(argc, argv, envp);
} else {
    setup_input_file(argv[1]);
    process_pipeline(argc, argv, envp);
}
```

### **After:**
```c
if (ft_strncmp(argv[1], "here_doc", 8) == 0) {
    process_commands(argc, argv, envp, 1);  // is_heredoc = 1
} else {
    setup_input_file(argv[1]);
    process_commands(argc, argv, envp, 0);  // is_heredoc = 0
}
```

---

## 🎯 **Why This is Good Design**

### **Single Responsibility Principle**
The function has one clear job: "Process a pipeline of commands"
- The mode (regular vs heredoc) is just a parameter
- All the core logic (malloc, loop, wait, free) is identical

### **Open/Closed Principle**  
- **Open for extension:** Easy to add new pipeline modes
- **Closed for modification:** Core logic doesn't change

### **Don't Repeat Yourself (DRY)**
- **Before:** 40+ lines of duplicate code
- **After:** Single function with smart parameters

---

## 🧪 **Testing the Refactored Version**

```bash
# Build with refactored main
cp src/main_refactored.c src/main.c
make

# Test both modes
./pipex input.txt "grep test" "wc -l" output.txt          # Regular
./pipex here_doc EOF "tr a-z A-Z" "wc -w" output.txt      # Heredoc
```

---

## 💡 **Key Takeaway**

This refactoring demonstrates **advanced programming thinking**:

1. **Pattern Recognition:** Spotting duplicate code
2. **Abstraction:** Finding the common pattern
3. **Parameterization:** Using flags to handle differences
4. **Norm Awareness:** Keeping within 42 constraints

**Excellent observation!** This kind of code review and improvement mindset is exactly what makes great programmers! 🚀

---

## 📊 **Final Stats**

| Metric | Before | After | Improvement |
|--------|--------|-------|-------------|
| **Functions in main.c** | 5 | 4 | ✅ Better |
| **Lines of duplicate code** | ~40 | 0 | ✅ Perfect |
| **Maintainability** | Medium | High | ✅ Better |
| **Norm compliance** | ✅ | ✅ | ✅ Same |
| **Functionality** | ✅ | ✅ | ✅ Same |

**This is production-quality refactoring!** 🏆
