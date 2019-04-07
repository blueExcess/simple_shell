#ifndef KEEPITSIMPLE_SHELL
#define KEEPITSIMPLE_SHELL

#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char **parser(char *str, char *delim);
int main(int ac, char *av[],char **env);
void record_history(char *input, size_t len, int startup);
unsigned int _wordCount(char *str);

#endif
