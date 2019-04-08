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


/* PROTOTYPES */

/* main.c */
int main(int ac, char *av[],char **env);
void record_history(char *input, ssize_t len);

/* parser.c */
char **parser(char *str, char *delim);

/* tools.c */
unsigned int _wordCount(char *str);


/* GLOBALS */
/**
 * flags - flags to use throughout program
 * @exit: if exit has been called
 * @startup: if startup processes need to be run
 */
struct flags
{
	bool exit;
	bool startup;
	bool interactive;
};
#endif
