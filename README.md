*This project has been created as part of the 42 curriculum by yblanco-, jugarcia.*

# Minishell

## Description

Minishell is a simplified Unix shell implemented in C. The goal of this project is to reproduce the core behavior of a real shell such as Bash by handling user input, parsing commands, and executing them while managing processes, pipes, and file descriptors.

The program reads commands from the standard input, interprets them, and executes them while supporting several typical shell features such as command pipelines, redirections, and environment variable expansion. Although it does not replicate all the functionality of Bash, it provides a functional command-line interpreter with a reduced but meaningful feature set.

This project focuses on understanding fundamental concepts of systems programming and operating systems, including process creation, inter-process communication, file descriptor management, signal handling, and command parsing.

## Features

Minishell implements a set of core shell functionalities:

* Interactive command prompt
* Execution of external programs
* Environment variable expansion (`$VAR`)
* Pipes (`|`)
* Input redirection (`<`)
* Output redirection (`>` and `>>`)
* Quote handling (`'` and `"`)
* Signal management (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
* Built-in command execution

## Built-in Commands

The following commands are implemented directly within Minishell without launching external binaries:

* `echo`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

## Instructions

### Compilation

Clone the repository and compile the project using the provided Makefile:

```bash
git clone "our repository"
cd minishell
make
```

This command compiles the project and generates the executable named `minishell`.

### Running the Program

After compilation, launch the shell with:

```bash
./minishell
```

Once running, you can enter commands just as you would in a normal Unix shell:

```bash
minishell$ ls -l
minishell$ echo "Hello world"
minishell$ cat file.txt | grep text
```

### Cleaning the Build

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To rebuild the project completely:

```bash
make re
```

## Project Structure

A typical project organization may look like the following:

```
minishell/
├── includes/
│   └── minishell.h
├── src/
│   ├── parser/
│   ├── executor/
│   ├── builtins/
│   └── main/
├── libft/
├── Makefile
└── README.md
```

The source code is typically divided into modules responsible for parsing input, executing commands, handling built-in functions, and managing signals.

## Technical Concepts

During the implementation of this project, several core Unix concepts are explored:

* Process creation using `fork`
* Program execution with `execve`
* Inter-process communication through pipes
* File descriptor manipulation with `dup` and `dup2`
* Signal handling
* Command parsing and tokenization
* Environment variable management

These components work together to emulate the behavior of a basic command-line interpreter.

## Resources

The following resources were useful for understanding the concepts required to implement this project:

* Bash Reference Manual
  https://www.gnu.org/software/bash/manual/

* Linux manual pages
  https://man7.org/linux/man-pages/

* POSIX documentation
  https://pubs.opengroup.org/onlinepubs/9699919799/


### AI Usage

Artificial intelligence tools were used during the development of this project to assist with the following tasks:

* Clarifying concepts related to Unix processes, pipes, and file descriptors
* Understanding the expected behavior of Bash in specific edge cases
* Reviewing implementation approaches and debugging strategies
* Assisting in the drafting of project documentation, including this README

All architectural decisions, algorithms, and the final implementation were designed and written by the project authors.

