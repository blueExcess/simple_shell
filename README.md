# simple_shell

## Description
A simple shell made for a Holberton Project.

## QUICK START
To start up this simple_shell, compile using 'gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell'.

run


	./simple_shell



##SYNOPSIS
simple_shell [command_string | file]

## DESCRIPTION
simple_shell is an sh-style command interpreter that executes commands read from the standard input or from a file.

## OVERVIEW
The shell is a command that reads lines from either a file or the terminal, interprets them, and generally executes other commands. It is the program that is running when a user types in ./simple_shell (users can use any shell they want, they must activate it though).

### SIMPLE COMMANDS
The leading word is interperated as a command, words after are interperated as arguments:

1. Commands can be from a builtin command, written and contained within the shell. Commands are also possibly from executable programs that the shell is finding and calling.

2. The remaining words entered into the shell will be tokenized and read as arguments for the command that came before them.

### BUILTINS
This section lists the available builtins.

#### env
This command with print out all of your machine's enviromental variables to the standard output.

#### cd [file/path/to/change/to]
Allows the user to change their current working directory.

#### exit
Allows the user to exit the simple_shell

### EXTERNAL FUNCTIONS
The simple_shell supports any functions that can be found within the PATH

#### EXAMPLE
cat, pwd, ls