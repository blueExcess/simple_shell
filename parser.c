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
	char **tokened, *token, **envc;

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
		global.command = _strdup(tokened[0], 0);
		global.command_length = _strlen(global.command);
	}
	free(token);
	return (tokened);
}


/**
 * fork_exec - creates a child process and executes the
 * written command if it's external
 * @path: path to check process with
 * @tokens: arguments from command line
 * @env: enviroment
 * Return: void
 */
void fork_exec(char *path, char **tokens, char **env)
{
	pid_t child;
	int status;

	if (!path)
	{
		basic_err();
		perror("command not found\n");
		return;
	}
/*switch runs one of the two cases, then runs the default after*/
	child = fork();
	if (child == -1)
	{
		basic_err();
		perror("fork failed\n");
		exit(103);
	}
	if (child == 0)
	{
		if (execve(path, tokens, env) == 0)
		{
			basic_err();
			perror("Execution failed\n");
			free(path);
			free(tokens);
		}
		exit(-1);
	}
	else
	{
		wait(&status);
		global.exit_status = WEXITSTATUS(global.exit_status);
	}
}

/**
 * com_remover - removew all comments marked by #
 * @path: the string from getline
 * Return: returns string with NULL in place of #
 */

char *com_remover(char *path)
{
	int index, count;

	for (index = 0; path[index] != '\0'; index++)
	{
		count = index;
		if (path[index] == '#')
		{
			if (path[--count] == ' ' ||
			    (path[--count] && path[++count] == ' '))
			{
				path[index] = '\0';
			}
		}
	}
	return (path);
}

int double_space_remover(char *path)
{
	int index;
	int count = 0;
	for (index = 0; path[index] != '\0'; index++)
	{
		if (path[index] == ' ')
		{
			count++;
			if (count  == _strlen(path))
				return (0);
		}
	}
	return (1);
}
