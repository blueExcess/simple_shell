/* file for parsing and calling functions */
#include "simpleshell.h"

char **parser(char *string, char *delim)
{
	unsigned int wrdCnt, index;
	char **tokened, *token, *command;

	wrdCnt = _wordCount(string);
	tokened = malloc((wrdCnt) * sizeof(char *));
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
		command = malloc(sizeof(char) * _strlen(tokened[0])); // NP
		/* NOT FREED */
		if (command == NULL)
			return (NULL); // set error flag?
		command = tokened[0]; // correct?
		globals.command = command;
		globals.command_length = _strlen(command);
	}
	return (tokened);
}


/*fork/exec function*/
void fork_exec(char *path, char **tokens,char **env)
{
// where do you call fork or execve or wait?
// currently I think it will only do one of the three per call (no loop)
	pid_t child = 0;


	if (!path)
	{
		perror("command not found\n");
		return;
	}
/*switch runs one of the two cases, then runs the default after*/
	switch (child = fork())
	{
	case -1:
		perror("fork failed\n");

		break;
	case 0:
		if (execve(path, tokens, env) == -1) // arg 2 needs to be of type *argv[] (all remaining arguments after *av[0])
			perror("Execution failed\n");
		break;
	default:
		free(path);
		if (wait(NULL) == -1)
			perror("wait failed\n");
		break;
	}
	free(tokens); // temp
}
