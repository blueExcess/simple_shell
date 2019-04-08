#include "basicshell.h"



char **parser(char *string, char *delim)
{
	unsigned int wrdCnt, index;
	char **tokened, *token;

	wrdCnt = _wordCount(string);
	tokened = malloc((wrdCnt + 1) * sizeof(char *));
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
	if (*tokened[0] == '/')
	{
		global.command = tokened[0];
	}
	return (tokened);
}

/*fork/exec function*/
void forkExec(char *argv[], char *path, char **env)
{
	pid_t child = 0;
	char *fullPath;

	fullPath = "bin/ls"; /*nate to make*/ /*search(argv[0], path);*/
	if (!fullPath)
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
		if (execve(fullPath, argv, env) == -1)
			perror("Execution failed\n");
		break;
	default:
		free(fullPath);
		if (wait(NULL) == -1)
			perror("wait failed\n");
		break;
	}
}
