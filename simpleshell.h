#ifndef KEEPITSIMPLE_SHELL
#define KEEPITSIMPLE_SHELL

/* HEADERS */
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>


/* PROTOTYPES */

/* main.c */
int main(int ac, char *av[],char **env);
void record_history(char *input, ssize_t len);
void print_prompt(void);
void startup(int ac, char **av);
void sig_handler(int n);

/* parser.c */
char **parser(char *str, char *delim);
void fork_exec(char *path, char **token, char **env);

/* search.c */
char *path_finder(char **env);
int search_builtins(char **args);

/* builtins.c */
int shell_exit(char **av);
int _cd(char **tokens);

/* tools.c */
unsigned int _wordCount(char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *str);
int *_astrlen(char **str);
char *_strdup(char *source, unsigned int extra);
void _strtostr(char *source, char *dest);
char *_strchr(char *str, int c);
void nl_cleaner(char *str);
void nl_remover(char *str);
char *_strcat(char *dest, char *src);
long int _atoi(char *str);
void fly_free(char **str);
char *cpyPath(char *input);
void updateDir(char *directory, char *beginning);



/* GLOBALS */

/**
 * flags - flags to use throughout program
 * @exit: if exit has been called
 * @startup: if startup processes need to be run
 * @interactive: if in interactive mode or not
 */
struct flags
{
	bool exit;
	bool startup;
	bool interactive;

}flags;

/**
 * global - global variables (not bool flags)
 * @command: name of command that's been parsed
 */
struct global
{
	char *command;
	int command_length;
	int line_no;
	int exit_status;
	int input;

}global;

#endif
