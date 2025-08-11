# PIPEX BONUS - COMPLETE STUDY GUIDE 📚

## 🎯 Overview: What Makes Bonus Different?

The bonus extends the mandatory 2-command pipeline to support:
1. **Multiple Commands** (3+ commands in a chain)
2. **Heredoc Functionality** (interactive input with delimiters)
3. **Append Mode** (>> instead of > for output)

---

## 🔄 Step-by-Step: How Bonus Works

### 📋 1. Command Line Parsing Logic

```c
int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    
    init_shell(&shell, argc, argv, envp);
    
    // Decision tree based on arguments
    if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
        here_doc(shell, argc, argv);        // Heredoc mode
    else if (argc >= 5)
        pipex(shell, argc, argv);           // Multi-command mode
    else
        show_usage_and_exit();              // Error: not enough args
}
```

**Key Differences from Mandatory:**
- Mandatory: Exactly 5 args (`./pipex infile cmd1 cmd2 outfile`)
- Bonus: 5+ args for multi-command, 6+ args for heredoc

---

### 🔧 2. Multi-Command Pipeline Flow

```
./pipex_bonus infile cmd1 cmd2 cmd3 cmd4 outfile
                ↓
         pipex(shell, argc, argv)
```

#### Step-by-Step Execution:

```c
static int pipex(t_shell shell, int argc, char **argv)
{
    int i;
    
    // STEP 1: Handle first command (reads from infile)
    pipex_run_first_cmd(&shell);
    
    // STEP 2: Handle middle commands (cmd2, cmd3, ...)
    i = 3;  // Start from argv[3] (second command)
    while (i < argc - 2)  // Stop before last command
    {
        repipe(&shell);           // Create new pipe
        process_cmd(&shell, argv[i++]);  // Execute command
    }
    
    // STEP 3: Handle last command (writes to outfile)
    unpipe(&shell);
    run_last_cmd_and_wait_all(&shell, O_WRONLY | O_CREAT | O_TRUNC);
    
    return (clean_exit(shell, 0));
}
```

---

### 🔄 3. The Magic of `repipe()` Function

**Purpose**: Connects commands in a chain by managing pipe transitions

```c
void repipe(t_shell *shell)
{
    // STEP 1: Close old connections
    close(shell->prev_read);        // Close previous input
    close(shell->pipe_fd[1]);       // Close current output
    
    // STEP 2: Shift pipes (output becomes next input)
    shell->prev_read = shell->pipe_fd[0];  // Current read becomes prev_read
    shell->pipe_fd[0] = -1;                // Clear current read
    
    // STEP 3: Create new pipe for next command
    pipe(shell->pipe_fd);  // New pipe: [0]=read, [1]=write
}
```

**Visual Example** (3 commands):
```
Initial:     infile → [cmd1] → pipe1
After repipe: pipe1 → [cmd2] → pipe2  
After repipe: pipe2 → [cmd3] → outfile
```

---

### 📝 4. Heredoc Functionality Deep Dive

```
./pipex_bonus here_doc DELIMITER cmd1 cmd2 outfile
                ↓
         here_doc(shell, argc, argv)
```

#### Heredoc Process:

```c
void heredoc_run_first_cmd(t_shell *shell)
{
    char *line;
    int limiter_len = ft_strlen(shell->argv[2]);  // DELIMITER length
    
    // STEP 1: Read lines from STDIN until delimiter
    while (1)
    {
        set_next_line(STDIN_FILENO, &line);  // Read line from user
        
        // STEP 2: Check if line matches delimiter
        if (!ft_strncmp(line, shell->argv[2], limiter_len - 1)
            && line[limiter_len] == '\n')
        {
            free(line);
            break;  // Stop reading
        }
        
        // STEP 3: Write line to pipe (becomes input for first command)
        write(shell->pipe_fd[1], line, ft_strlen(line));
        free(line);
    }
    
    // STEP 4: Start processing commands
    repipe(shell);
    process_cmd(shell, shell->argv[3]);  // First command after heredoc
}
```

**What happens:**
1. User types lines interactively
2. Each line goes into a pipe
3. When delimiter is found, stop reading
4. The accumulated lines become input for first command

---

## 🏗️ How to Rebuild From Ground Up

### Phase 1: Start with Mandatory Base

```c
// 1. Basic structure (mandatory)
typedef struct s_shell {
    int argc;
    char **argv;
    char **envp;
    char *bin_paths;
    int waits;
    int prev_read;
    int pipe_fd[2];  // [0]=read, [1]=write
} t_shell;

// 2. Core functions
void init_shell(t_shell *shell, int argc, char **argv, char **envp);
void process_cmd(t_shell *shell, char *cmd);
void repipe(t_shell *shell);
void unpipe(t_shell *shell);
```

### Phase 2: Add Multi-Command Support

```c
// 1. Modify main to accept variable arguments
int main(int argc, char **argv, char **envp)
{
    if (argc >= 5)  // Change from argc == 5
        pipex(shell, argc, argv);
    // ...
}

// 2. Create loop for multiple commands
static int pipex(t_shell shell, int argc, char **argv)
{
    pipex_run_first_cmd(&shell);  // Handle first command
    
    // NEW: Loop through middle commands
    int i = 3;
    while (i < argc - 2)
    {
        repipe(&shell);
        process_cmd(&shell, argv[i++]);
    }
    
    // Handle last command
    run_last_cmd_and_wait_all(&shell, O_TRUNC);
}
```

### Phase 3: Add Heredoc Support

```c
// 1. Add heredoc detection
if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
    here_doc(shell, argc, argv);

// 2. Implement heredoc reading
void heredoc_run_first_cmd(t_shell *shell)
{
    // Read from STDIN until delimiter
    // Write to pipe
    // Start command processing
}

// 3. Use append mode for heredoc output
run_last_cmd_and_wait_all(&shell, O_APPEND);  // >> instead of >
```

### Phase 4: Create Helper Functions

```c
// Separate first command handling
void pipex_run_first_cmd(t_shell *shell)
{
    shell->prev_read = open(shell->argv[1], O_RDONLY);
    process_cmd(shell, shell->argv[2]);
}

// Separate last command handling
void run_last_cmd_and_wait_all(t_shell *shell, int flags)
{
    shell->pipe_fd[1] = open(shell->argv[shell->argc - 1], flags, 0644);
    process_cmd(shell, shell->argv[shell->argc - 2]);
    
    // Wait for all child processes
    while (shell->waits--)
        wait(NULL);
}
```

---

## 🔍 Key Concepts Explained

### 1. **File Descriptor Management**

```
Command Chain: cmd1 | cmd2 | cmd3

Initial state:
prev_read = infile_fd
pipe_fd = [pipe1_read, pipe1_write]

After cmd1:
prev_read = pipe1_read  (cmd2 reads from here)
pipe_fd = [pipe2_read, pipe2_write]  (cmd2 writes here)

After cmd2:
prev_read = pipe2_read  (cmd3 reads from here)
pipe_fd = [outfile_fd, -1]  (cmd3 writes to file)
```

### 2. **Process Synchronization**

```c
// Each process_cmd() increments waits counter
if (pid && ++shell->waits)
    return;  // Parent continues, child executes

// At the end, wait for all children
while (shell->waits--)
    wait(NULL);  // Ensures all commands complete
```

### 3. **Heredoc vs Regular Input**

**Regular**: `infile → cmd1 → cmd2 → outfile`
**Heredoc**: `user_input → pipe → cmd1 → cmd2 → appendfile`

---

## 🧪 Testing Your Implementation

### Test 1: Multi-Command
```bash
# 3 commands
./pipex_bonus numbers.txt "sort -n" "head -3" "wc -l" output.txt

# 4 commands  
./pipex_bonus input.txt "grep word" "tr a-z A-Z" "sort" "uniq" output.txt
```

### Test 2: Heredoc
```bash
# Interactive input
./pipex_bonus here_doc EOF "cat -n" "wc -l" output.txt
# Type lines, end with "EOF"

# Piped input
echo -e "line1\nline2\nEOF" | ./pipex_bonus here_doc EOF "wc -w" output.txt
```

### Test 3: Edge Cases
```bash
# Many commands
./pipex_bonus in.txt "cmd1" "cmd2" "cmd3" "cmd4" "cmd5" out.txt

# Heredoc with multiple commands
./pipex_bonus here_doc STOP "tr a-z A-Z" "sort" "uniq -c" append.txt
```

---

## 🚨 Common Pitfalls & Solutions

### 1. **Pipe Management**
**Problem**: Forgetting to close pipes leads to hanging processes
**Solution**: Always close unused pipe ends in child processes

### 2. **Heredoc Delimiter Matching**
**Problem**: Incorrect string comparison for delimiter
**Solution**: Compare exact length and check for newline

### 3. **Argument Indexing**
**Problem**: Off-by-one errors in argv indexing
**Solution**: Draw out the argument positions:
```
Regular:  [0]pipex [1]infile [2]cmd1 [3]cmd2 [4]outfile
Heredoc:  [0]pipex [1]here_doc [2]delim [3]cmd1 [4]cmd2 [5]outfile
```

### 4. **Memory Leaks**
**Problem**: Not freeing allocated memory in error cases
**Solution**: Use consistent cleanup functions

---

## 💡 Pro Tips for Implementation

1. **Start Simple**: Get 3-command pipeline working first
2. **Debug with Prints**: Add debug output to trace pipe states
3. **Test Incrementally**: Test each new feature separately
4. **Use Valgrind**: Check for memory leaks and file descriptor leaks
5. **Compare with Shell**: Always verify against actual shell behavior

---

## 📚 Study Checklist

- [ ] Understand `repipe()` pipe rotation concept
- [ ] Trace through 3-command execution step by step
- [ ] Implement heredoc reading with delimiter detection
- [ ] Handle variable argument parsing correctly
- [ ] Test with different numbers of commands
- [ ] Verify proper file descriptor cleanup
- [ ] Compare output with shell equivalents

---

*This guide provides everything you need to understand and rebuild the bonus functionality from scratch! 🚀*
