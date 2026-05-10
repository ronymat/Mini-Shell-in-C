# Mini Shell in C

A custom Linux Mini Shell implemented in C that simulates core shell functionalities including command execution, built-in commands, piping, job control, signal handling, and prompt customization.

## Overview

This project is a simplified Linux shell developed in C using POSIX system calls and Linux system programming concepts.

The shell accepts user input, identifies whether the command is built-in or external, creates child processes for execution, supports piping between commands, and manages foreground/background jobs.

This project demonstrates practical understanding of process creation, signal handling, command parsing, inter-process communication, and shell behavior.

---

## Features

### Built-in Commands

Supported built-in commands:

- `cd` → Change current directory
- `pwd` → Print working directory
- `exit` → Exit shell
- `echo $$` → Display shell PID
- `echo $?` → Display exit status of last command
- `echo $SHELL` → Display shell path
- `jobs` → Show stopped jobs
- `fg` → Resume stopped job in foreground
- `bg` → Resume stopped job in background

---

### External Command Execution

Execute Linux commands such as:

```bash
ls
date
ps
cat
grep
wc
sleep
```

External commands are preloaded from `external_cmd.txt` for faster command lookup.

---

### Pipe Support

Supports command piping:

```bash
ls | wc
cat file.txt | grep hello
ps | grep bash
```

Multiple command pipelines are supported.

---

### Job Control

Supports job management:

```bash
sleep 100
Ctrl + Z
jobs
fg
bg
```

Features:

- store stopped jobs
- foreground execution
- background execution
- job listing

---

### Signal Handling

Handles:

- `Ctrl + C` (`SIGINT`)
- `Ctrl + Z` (`SIGTSTP`)

Behavior:

- returns safely to shell prompt
- prevents shell termination
- manages child process interruption correctly

---

### Prompt Customization

Default prompt:

```bash
minishell:~$
```

Change prompt dynamically:

```bash
PS1=my_shell
```

Result:

```bash
my_shell:~$
```

---

### Command Parsing

Shell parses:

- command name
- arguments
- pipelines
- built-in commands
- external commands

---

## Technologies Used

- C Programming
- Linux System Programming
- POSIX APIs
- Process Management
- Signal Handling
- Linked Lists
- Inter-process Communication

---

## POSIX System Calls Used

This project uses:

- `fork()`
- `execvp()`
- `wait()`
- `waitpid()`
- `pipe()`
- `dup2()`
- `open()`
- `close()`
- `chdir()`
- `getcwd()`
- `signal()`
- `kill()`
- `getpid()`
- `getenv()`

---

## Build Instructions
manually:

```bash
gcc main.c scan_input.c commands.c exec_internal.c exec_external.c link.c -o minishell
```

## Data Structures Used

### Linked List

Used for job control:

Stores:

- process ID
- command string
- next node pointer

Used by:

- `jobs`
- `fg`
- `bg`

---

## Key Concepts Demonstrated

This project demonstrates:

- shell architecture
- process creation
- command parsing
- signal handling
- job control
- piping
- linked list management
- file operations
- system programming
- inter-process communication

---

## Future Improvements

Possible enhancements:

- input/output redirection (`>`, `<`, `>>`)
- command history
- auto-completion
- environment variable expansion
- alias support
- command chaining (`&&`, `||`)
- wildcard support

---

## Author

**Rony Mathew**  
Electronics and Communication Engineering Graduate  
Embedded / Linux Systems Enthusiast
