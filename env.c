/* env builtin - to be added to builtins.c */
#include "simpleshell.h"

int _env(void)
{
	extern char **environ;
	char **c_env = environ;
	int *env_len, x = 0, i = 0;

	env_len = _astrlen(c_env);
	for (; c_env[i]; i++)
	{
		write(STDOUT_FILENO, c_env[i], env_len[i + 1]);
		write(STDOUT_FILENO, "\n", 2);
	}
	return (0);
}
