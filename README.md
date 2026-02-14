*This project has been created as part of the 42 curriculum by kebris-c, lkoualla.*

# Minishell

## Description

Minishell is a minimal Unix shell implemented in C, developed as part of the 42 school curriculum.  
The goal of this project is to gain a deep understanding of how shells work internally by recreating core functionalities of Bash, including command parsing, process creation, pipes, redirections, environment handling, and signal management.

This project focuses on low-level system programming concepts such as:
- Process control (`fork`, `execve`, `wait`...)
- File descriptors and redirections
- Inter-process communication via pipes
- Signal handling
- Robust parsing and memory management

The result is a functional interactive shell that behaves similarly to Bash for a defined subset of features.

## Instructions

### Compilation

To compile the project, simply run:
```bash
make
```

Additional available Makefile rules:
```bash
make re       # Recompile the project from scratch
make clean    # Remove object and dependence files
make fclean   # Remove objects, dependences and the executable
```

### Execution
Once compiled, launch minishell with:
```bash
./minishell
```
You will enter an interactive shell prompt (`minishell$ `) where you can execute commands similarly to Bash.

## Technical Decisions

### Tokenizer and Parsing Strategy

The shell input is processed using a custom tokenizer based on linked lists.
Each token represents a word or operator and is associated with a specific type (`T_WORD`, `T_PIPE`, `T_REDIR_APPEND`, `T_REDIR_IN`, `T_REDIR_OUT` or `T_HEREDOC`).

This design allows:
- Clear separation between lexical analysis and execution logic
- Easier handling of complex command lines with pipes and redirections
- Better extensibility and maintainability of the parser

The tokenizer produces a structured representation of the input that is later transformed into execution units.

## Resources

### Classical References

- GNU Bash Manual
- man: bash, execve, fork, pipe, dup2
- Old projects as `pipex`.

### Use of Artificial Intelligence

AI tools were used strictly as support, not as a replacement for understanding or implementation.

Their usage was limited to:
- Acting as a conceptual tutor at critical decision points
- Clarifying theoretical concepts, especially related to signal handling
- Guiding discussions around async-signal-safe functions, helping identify which functions are safe or unsafe to use inside signal handlers and why

All design decisions, implementations, and final code were written and validated by the authors.

## Authors
kebris-c — 42 login
lkoualla — 42 login
