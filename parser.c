/* file for parsing and calling functions */
#include "simpleshell.h"

/**
 * parser - parses a single string in to strings inside a string
 * @string: incoming string
 * @delim: delimiter to parse string with
 * Return: returns a double pointer containing tokens
 */

char **parser(char *string, char *delim)
{
	unsigned int wrdCnt, index;
	char **tokened, *token, *command, **envc, *comment;

	string = com_remover(string);
	envc = environ;

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
	if (tokened[0][0] != '/')
	{
		/* command = malloc(sizeof(char) * _strlen(tokened[0]) + 1); // NP */
		/* /\* NOT FREED *\/ */
		/* if (command == NULL) */
		/* 	return (NULL); // set error flag? */
		global.command = _strdup(tokened[0], 0);
		/* global.command = command; */
		global.command_length = _strlen(global.command);
	}
	else if (*tokened[0] == '/')
		if (!(access(tokened[0], F_OK)))
			fork_exec(tokened[0], tokened, envc);
	return (tokened);
}


/**
 * fork_exec - creates a child process and executes the written command if it's external
 * @path: path to check process with
 * @token: arguments from command line
 * @env: enviroment
 * Return: void
 */
void fork_exec(char *path, char **tokens, char **env)
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
		exit(103);
	}
	if (child == 0)
	{
		execve(path, tokens, env);
		/* perror("Execution failed\n"); */
		// not our exit function
	        exit(-1);
	}
	else
		wait(&status);
}
