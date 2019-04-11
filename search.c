/* functions for searching things */
#include "simpleshell.h"

char *path_finder(char **env)
{
	char **env_copy = env, **parsed_path;
	char *name = "PATH=", *path_str_ptr, *path_to_check;
	int i, *path_lengths, num_tokens, str_len, access_check;

/* find matching env variable */
	for (i = 0; *env_copy; i++, env_copy++)
	{
		if (_strncmp(*env_copy, name, 5) == 0)
			break;
	}
/* set pointer to = in env and move to next value */
	path_str_ptr = (_strchr(env_copy, '=')) + 1;
/* copy path to new str */
	path_str = _strcpy(path_str_ptr, 1); // null included?
/* pass path to tokenizer */
	parsed_path = parser(path_str, ':');
	free(path_str);
/* get length of every string after parsing */
	path_lengths = _astrlen(parsed_path);
/* get number of tokens in path */
	num_tokens = path_lengths[0];
	i = 0;

/* allocate mem for new string (sub of path) and command */
/* add '/' and command, then check if file exists. */
/* loop will end when existence is verified or end of array */
	do{
		path_to_check = malloc(sizeof(char) * path_lengths[i + 1]
			       + 2 + sizeof(char) * globals.command_length);
		path_to_check = parsed_path[i];
		str_len = path_lengths[i + 1];
		path_to_check[str_len] = '/';
		_strtostr(globals.command, path_to_check[str_len + 1]);
		access_check = access(path_to_check, F_OK);
		if (access_check)
			free(path_to_check);
		i++;
	} while (access_check || i < num_tokens);
/* for testing, will return to main. Actual will sent to forkExec */
	if (i == num_tokens)
		return (NULL); // will search builtins
	return (path_to_check);
}
