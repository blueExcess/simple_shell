/* file for parsing and calling functions */
#include "simpleshell.h"

char **parser(char *string, char *delim)
{
	unsigned int wrdCnt, index;
	char **tokened, *token, *command;

	wrdCnt = _wordCount(string);
	tokened = malloc((wrdCnt + 1) * sizeof(char *));
	/* malloced */
	if (!tokened)
	{
		perror("Memory Allocation failed\n");
		return ('\0');
	}
	tokened[0] = token = strtok(string, delim);

	for (index = 1; token != NULL; index++)
	{
		tokened[index] = token = strtok('\0', delim);
	}
	if (*tokened[0] != '/')
	{
		/* command = malloc(sizeof(char) * _strlen(tokened[0]) + 1); // NP */
		/* /\* NOT FREED *\/ */
		/* if (command == NULL) */
		/* 	return (NULL); // set error flag? */
		global.command = _strdup(tokened[0], 0);
		/* global.command = command; */
		global.command_length = _strlen(global.command);
	}
	return (tokened);
}


/*fork/exec function*/
void fork_exec(char *path, char **tokens,char **env)
{
	pid_t child;
	int status;

	if (!path)
	{
		perror("command not found\n");
		return;
	}
/*switch runs one of the two cases, then runs the default after*/
	child = fork();
	if (child == -1)
	{
		perror("fork failed\n");
	}
	if (child == 0)
	{
		execve(path, tokens, env);
		perror("Execution failed\n");
		// not our exit function
	        exit(-1);
	}
	else
		wait(&status);
}
