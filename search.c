/* functions for searching things */
#include "simpleshell.h"

/**
 * path_finder - finds the current enviromental path and checks if a
 * function can run in it
 * @env: enviromental variables
 * Return: returns path to check
 */

char *path_finder(char **env)
{
	char **env_copy = env, **parsed_path;
	char *name = "PATH=", *path_str_ptr, *path_to_check;
	char *path_str;
	int i, *path_lengths, num_tokens, str_len, access_check;
	bool flag = false;

	for (i = 0; *env_copy; i++, env_copy++)
	{
		if (strncmp(*env_copy, name, 5) == 0)
			break;
	}
	path_str_ptr = (_strchr(*env_copy, '=')) + 1;
	path_str = _strdup(path_str_ptr, 0);
	for (i = 0; path_str[i]; i++)
		if (path_str[i] == ':' && path_str[i + 1] == ':')
			flag = true;
	parsed_path = parser(path_str, ":");
	path_lengths = _astrlen(parsed_path);
	num_tokens = path_lengths[0];
	i = 0;
	do {
		path_to_check = parsed_path[i];
		path_to_check = _strdup(parsed_path[i],
					2 + global.command_length);
		str_len = path_lengths[i + 1];
		path_to_check[str_len] = '/';
		path_to_check = _strcat(path_to_check, global.command);
		access_check = access(path_to_check, F_OK);
		if (access_check != 0)
		{
			free(path_to_check);
		}
		i++;
	} while (access_check && i < num_tokens);
	if (flag)
		if (access(global.command, F_OK) == 0)
			return (global.command);
	if (i == num_tokens)
		return (NULL);
	return (path_to_check);
}


/**
 * search_builtins - search and execute any builtins
 * @av: list of all tokenized args
 *
 * Return: 0 on success, 1 if not found, -1 if error
 */
int search_builtins(char **av)
{
	char *exit = "exit", *cd = "cd", *env = "env", *setenv = "setenv";
	char *unsetenv = "unsetenv", *help = "help", *history = "history";
	int error = 0;

	if (_strcmp(global.command, exit) == 0)
		return (shell_exit(av));
	if (_strcmp(global.command, cd) == 0)
		return (_cd(av));
	if (_strcmp(global.command, env) == 0)
		return (_env());
	if (_strcmp(global.command, setenv) == 0)
	{
		return (0);
	}
	if (_strcmp(global.command, unsetenv) == 0)
	{
		return (0);
	}
	if (_strcmp(global.command, help) == 0)
	{
		return (0);
	}
	if (_strcmp(global.command, history) == 0)
	{
		return (0);
	}
	if (error)
		return (-1);
	return (1);
}
