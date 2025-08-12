# 🚫 No Global Variables - Solutions for Simple Approach

## 🎯 The Problem
42 projects typically forbid global variables, but our simple approach used:
```c
static int g_child_count = 0;  // ❌ FORBIDDEN
```

## ✅ Solution 1: PID Array (Recommended)

**Concept**: Store all child PIDs in an array, then wait for them at the end.

```c
int main(int argc, char **argv, char **envp) {
    pid_t *pids;           // Array to store PIDs
    int pid_count = 0;     // Counter (local variable)
    int max_pids = argc - 3;  // Maximum possible commands
    
    pids = malloc(sizeof(pid_t) * max_pids);
    
    // Process commands
    while (i < argc - 2)
        child_process_with_pid_storage(argv[i++], envp, &pids, &pid_count);
    
    // Wait for all at the end
    wait_for_pids(pids, pid_count);
    free(pids);
}
```

**Benefits:**
- ✅ No globals - everything is local
- ✅ Explicit PID tracking
- ✅ Easy to debug (you can see all PIDs)
- ✅ Memory is properly managed

---

## ✅ Solution 2: Wait-Any Loop

**Concept**: Use `wait()` in a loop until no more children exist.

```c
void wait_for_all_children(void) {
    int status;
    
    // Keep waiting until no more children
    while (wait(&status) > 0)
        ;  // Do nothing, just wait for next child
}

int main(int argc, char **argv, char **envp) {
    // ... process all commands without storing PIDs ...
    
    // Wait for all children (however many there are)
    wait_for_all_children();
    
    // Execute last command
    execute(argv[argc - 2], envp);
}
```

**Benefits:**
- ✅ No globals needed
- ✅ Very simple implementation
- ✅ Automatically handles any number of children
- ✅ No memory allocation needed

---

## ✅ Solution 3: Recursive Approach

**Concept**: Each function calls the next, creating a natural stack-based tracking.

```c
void process_remaining_commands(char **argv, char **envp, int current_cmd, int last_cmd) {
    if (current_cmd >= last_cmd) {
        // Base case: no more middle commands
        return;
    }
    
    int fd[2];
    pid_t pid;
    
    pipe(fd);
    pid = fork();
    
    if (pid == 0) {
        // Child: execute current command
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute(argv[current_cmd], envp);
    } else {
        // Parent: continue with next command
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        
        // Recursively process remaining commands
        process_remaining_commands(argv, envp, current_cmd + 1, last_cmd);
        
        // Wait for this child when recursion returns
        waitpid(pid, NULL, 0);
    }
}
```

---

## 🏆 **Recommended Solution: PID Array**

I've implemented **Solution 1** in `pipex_bonus_no_globals.c` because:

1. **Most Explicit** - You can see exactly what's happening
2. **Best for Debugging** - Easy to trace which processes are running
3. **Memory Safe** - Clean allocation and cleanup
4. **42-Style Friendly** - Follows typical 42 project patterns

### Key Changes Made:

```c
// OLD (with global):
static int g_child_count = 0;

void child_process(char *cmd, char **envp) {
    // ... fork and setup ...
    g_child_count++;  // ❌ Global modification
}

void wait_for_all_children(void) {
    while (g_child_count > 0) {
        wait(NULL);
        g_child_count--;
    }
}
```

```c
// NEW (no globals):
void child_process_with_pid_storage(char *cmd, char **envp, pid_t **pids, int *pid_count) {
    // ... fork and setup ...
    (*pids)[*pid_count] = pid;  // ✅ Store PID in array
    (*pid_count)++;             // ✅ Increment local counter
}

void wait_for_pids(pid_t *pids, int pid_count) {
    int i = 0;
    while (i < pid_count) {
        waitpid(pids[i], NULL, 0);  // ✅ Wait for specific PID
        i++;
    }
}
```

---

## 🧪 Testing the No-Globals Version

```bash
cd new/
gcc -Wall -Wextra -Werror -I../include pipex_bonus_no_globals.c utils_bonus_fixed.c ../libft_full/libft_full.a -o pipex_no_globals

# Test it
./pipex_no_globals input.txt "grep test" "wc -l" output.txt
./pipex_no_globals input.txt "sort" "head -3" "wc -l" output.txt
```

---

## 📊 **Comparison Summary**

| Approach | Globals | Memory | Complexity | Debug |
|----------|---------|--------|------------|-------|
| **PID Array** | ❌ None | Small malloc | Low | Easy |
| **Wait-Any** | ❌ None | None | Very Low | Medium |
| **Recursive** | ❌ None | Stack | Medium | Hard |

**Winner: PID Array** - Best balance of simplicity, clarity, and debuggability! 🏆

---

## 💡 **Pro Tip**

The PID array approach is actually **more robust** than the global variable approach because:
- You can handle specific process failures
- You can get exit codes from specific commands
- You have full control over the waiting order
- It's easier to add features like timeouts or signal handling

**You've actually improved the code by removing globals!** 🚀
