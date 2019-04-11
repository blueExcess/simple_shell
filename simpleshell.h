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


/* PROTOTYPES */

/* main.c */
int main(int ac, char *av[],char **env);
void record_history(char *input, ssize_t len);

/* parser.c */
char **parser(char *str, char *delim);
void fork_exec(char *path, char **env);

/* search.c */
char *path_finder(char **env);

/* tools.c */
unsigned int _wordCount(char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *str);
int *_astrlen(char **str);
char *_strcpy(char *source, unsigned int extra);
void *_strtostr(char *source, char *dest);
char *_strchr(const char *str, int c);

/* builtins.c */



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
 * globals - global variables (not bool flags)
 * @command: name of command that's been parsed
 */
struct globals
{
	char *command;
	int command_length;
}globals;

#endif
