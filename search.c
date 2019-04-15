/* functions for searching things */
#include "simpleshell.h"

char *path_finder(char **env)
{
	char **env_copy = env, **parsed_path;
	char *name = "PATH=", *path_str_ptr, *path_to_check;
	char *path_str, *temp;
	int i, *path_lengths, num_tokens, str_len, access_check;
	int x = 0; //debug

/* find matching env variable */
	for (i = 0; *env_copy; i++, env_copy++)
	{
		if (strncmp(*env_copy, name, 5) == 0)
			break;
	}
/* set pointer to = in env and move to next value */
	path_str_ptr = (_strchr(*env_copy, '=')) + 1;
	printf("path_str_ptr: %s\n", path_str_ptr); //debug

/* copy path to new str */
	path_str = _strdup(path_str_ptr, 0);
	printf("path_str: %s\n", path_str); // debug

/* pass path to tokenizer */
	parsed_path = parser(path_str, ":");

	/* DEBUG */
	for (; parsed_path[x]; x++)
		printf("parsed_path[%d]: %s\n", x, parsed_path[x]);

/*	free(path_str);*/
/* get length of every string after parsing */
	path_lengths = _astrlen(parsed_path);

	/* DEBUG */
	for (x = 0; x <= path_lengths[0]; x++)
		printf("path_length[%d]: %d\n", x, path_lengths[x]);

/* get number of tokens in path */
	num_tokens = path_lengths[0];
	i = 0;

/* allocate mem for new string (sub of path) and command */
/* add '/' and command, then check if file exists. */
/* loop will end when existence is verified or end of array */
	do{
		/* path_to_check = malloc(sizeof(char) * path_lengths[i + 1] */
		/* 	       + 2 + sizeof(char) * global.command_length); */
		/* if (path_to_check == NULL) */
		/* 	return (NULL); // RTP */
		/* DEBUG */
		printf("global.command: %s\nglobal.command_len: %d\n",
		       global.command, global.command_length);

		printf("parsed_path[%d]: %s\n", i, parsed_path[i]); // debug
		path_to_check = parsed_path[i];
		printf("(after sets new path to check) i: %d\n", i); // debug
		printf("path_to_check: %s, len: %zd\n", path_to_check, strlen(path_to_check)); // debug
		path_to_check = _strdup(parsed_path[i],
					2 + global.command_length);
		printf("path_to_check: %s\n", path_to_check); // debug
		str_len = path_lengths[i + 1];
		printf("str_len: %d\n", str_len); // debug
		path_to_check[str_len] = '/';
		path_to_check[str_len + 1] = '\0';
		printf("path_to_check: %s\n", path_to_check); // debug
		printf("strlen: %zd\n", strlen(path_to_check)); // debug
		path_to_check = _strcat(path_to_check, global.command);
		printf("path_to_check: %s\n", path_to_check); // debug
		printf("strlen: %zd\n", strlen(path_to_check)); // debug
		access_check = access(path_to_check, F_OK);
		if (access_check == 0)
		{
			puts("passed access check"); // debug
			free(path_to_check);
		}
		i++;
	} while (access_check && i < num_tokens);
/* for testing, will return to main. Actual will sent to forkExec */
	if (i == num_tokens)
		return (NULL); // will search builtins
	return (path_to_check);
}


/**
 * search_builtins - search and execute any builtins
 * @argv: list of all tokenized args
 *
 * Return: 0 on success, 1 if not found, -1 if error
 */
int search_builtins(char **av)
{
/* too long -- may need second builtin search function */
	extern char **environ;
	char **cp_env = environ;
	char *exit = "exit", *cd = "cd", *env = "env", *setenv = "setenv";
	char *unsetenv = "unsetenv", *help = "help", *history = "history";
	int error = 0;

	// need to set any flags for running builtins?

	if (_strcmp(global.command, exit) == 0)
		return (shell_exit(av));
	if (_strcmp(global.command, cd) == 0)
	{
		_cd(av);
		// run cd function
		// set any flags?
		return (0);
	}
	if (_strcmp(global.command, env) == 0)
	{
		// run env function
		return (0);
	}
	if (_strcmp(global.command, setenv) == 0)
	{
		// run setenv function
		return (0);
	}
	if (_strcmp(global.command, unsetenv) == 0)
	{
		// run unsetenv function
		return (0);
	}
	if (_strcmp(global.command, help) == 0)
	{
		// run help function
		return (0);
	}
	if (_strcmp(global.command, history) == 0)
	{
		// run history function
		return (0);
	}
/* exe error */
	if (error)
		return (-1); // and set errno flags?
	return (1); // builtin not found
}
