# Pipex

## Overview
**Pipex** is a 42 school project that aims to reproduce the behavior of the shell pipeline (`|`). It allows executing two commands where the output of the first command is used as the input for the second command, similar to:

```bash
< infile cmd1 | cmd2 > outfile
```

The project helps in understanding UNIX file descriptors, pipes, and process management in depth.

---

## Features
- Simulates the behavior of `|` (pipe operator) in the shell.
- Supports input and output redirection.
- Works with absolute and relative paths for commands.
- Handles errors and edge cases gracefully.
- Implements process handling using `fork()` and `execve()`.
- Supports multiple pipes (bonus feature).
- Implements "here_doc" functionality (bonus feature).

---

## How It Works
### **General Concept**
1. Open the input file (`infile`) for reading.
2. Create a pipe using `pipe()`, which provides a way for processes to communicate.
3. Fork the first child process:
   - Redirect `infile` to `stdin`.
   - Redirect the write end of the pipe to `stdout`.
   - Execute `cmd1`.
4. Fork the second child process:
   - Redirect the read end of the pipe to `stdin`.
   - Redirect `stdout` to `outfile`.
   - Execute `cmd2`.
5. Close unnecessary file descriptors and wait for child processes to finish.

### **Process Flow**
```plaintext
Parent Process
    ├── fork() → Child 1 (Executes cmd1, writes to pipe)
    ├── fork() → Child 2 (Executes cmd2, reads from pipe)
    ├── Wait for both children
```

---

## Installation
Clone the repository:

```bash
git clone https://github.com/mel-adna/1337_Pipex.git
cd 1337_Pipex
```

Compile the program using:

```bash
make
```

This will generate the executable **pipex**.

---

## Usage
Run **pipex** as follows:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example:

```bash
./pipex input.txt "ls -l" "wc -l" output.txt
```
This executes:
```bash
ls -l < input.txt | wc -l > output.txt
```

### **Bonus Features**
- **Multiple Pipes:**
  ```bash
  ./pipex_bonus infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
  ```
  Equivalent to:
  ```bash
  < infile cmd1 | cmd2 | cmd3 ... | cmdN > outfile
  ```

- **Here Document (`<<` and `>>` support):**
  ```bash
  ./pipex_bonus here_doc LIMITER cmd cmd1 file
  ```
  Equivalent to:
  ```bash
  cmd << LIMITER | cmd1 >> file
  ```

---

## Implementation Tricks
### **Handling `execve` Paths**
- The program extracts possible paths from the `PATH` environment variable.
- Uses `access()` to check if the command exists in those paths.
- Calls `execve()` with the correct path.

### **File Descriptor Management**
- The parent process closes unused ends of the pipe to prevent deadlocks.
- Proper redirection of stdin/stdout using `dup2()`.

### **Error Handling**
- Checks for missing arguments and file access permissions.
- Handles `fork()` failures and process execution errors.
- Ensures no memory leaks by freeing all allocated resources.

---

## Common Errors & Fixes
| Error | Possible Cause | Solution |
|--------|----------------|-----------|
| `Permission denied` | Trying to open a read-only or protected file | Check file permissions with `ls -l` |
| `command not found` | Command is not in `PATH` or mistyped | Use `which cmd1` to check the correct path |
| `No such file or directory` | The input file does not exist | Make sure the file exists and has the right path |
| `Segmentation fault` | Unhandled null pointers or memory issues | Use `gdb` or `valgrind` to debug |

---

## Submission Guidelines
- Submit the project to your assigned **Git repository**.
- Ensure that your repository contains:
  - `Makefile`
  - All source files (`.c` and `.h`)
  - README.md (this file)
- Your code must follow the **42 Norm**.
- No memory leaks or segmentation faults are allowed.
- Bonus is evaluated **only if the mandatory part is perfect**.

---

## Credits
Project completed by [mel-adna](https://github.com/mel-adna) as part of 1337 School's curriculum.

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

