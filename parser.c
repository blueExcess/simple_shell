/* file for parsing and calling functions */
#include "simpleshell.h"

char **parser(char *string, char *delim)
{
	unsigned int wrdCnt, index;
	char **tokened, *token;

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
		globals.command = tokened[0];
	}
	return (tokened);
}

/*fork/exec function*/
void fork_exec(char *path, char **env)
{
	pid_t child = 0;
	char *command;

	command = malloc(_strlen(globals.command) * sizeof(char *));
	command = globals.command;

	if (!path)
	{
		perror("command not found\n");
		return;
	}

	switch (child = fork())
	{
	case -1:
		perror("fork failed\n");

		break;
	case 0:
		if (execve(path, command, env) == -1)
			perror("Execution failed\n");
		break;
	default:
		free(path);
		if (wait(NULL) == -1)
			perror("wait failed\n");
		break;
	}
	free(globals.command); // temp
}
