#include "simpleshell.h"

int _cd(char **tokens)
{
	int index = 0;
	char *newPath;
	char buffer[2048];

	while (tokens[++index])
		;
	if (index < 2)
	{
		newPath = cpyPath("HOME=");
		getcwd(buffer, sizeof(tokens));
		updateDir(buffer, "OLDPWD=");
		if (chdir(newPath) != 0)
		{
			perror("");
		}
		getcwd(buffer, sizeof(buffer));
		updateDir(buffer, "PWD=");
	}
	else
	{
		if (tokens[1][0] == '-')
		{
			newPath = cpyPath("OLDPWD=");
			getcwd(buffer, sizeof(buffer));
			updateDir(buffer, "OLDPWD=");
			if (chdir(newPath) != 0)
				perror("");
			getcwd(buffer, sizeof(buffer));
			updateDir(buffer, "PWD=");
		}
		else
		{
			getcwd(buffer, sizeof(buffer));
			updateDir(buffer, "OLDPWD=");
			if (chdir(tokens[1] != '\0'))
				perror("");
			getcwd(buffer, sizeof(buffer));
			updateDir(buffer, "PWD=");
		}
	}
	return (1);
}

/**
 * exit - will exit the shell and close everything down
 * @av: argv to collect exit status
 *
 * Return: 0 on success, -1 on error
 */
int shell_exit(char **av)
{
	char *status = av[1];
	char *error = "exit: Illegal number: ", *ferror;
	int i = 0;
	long int value = 0;
	bool err = false;

	if (status)
	{
		ferror = _strdup(error, _strlen(status));
		ferror = _strcat(ferror, status);
		for (; status[i]; i++)
			if ((status[i] == '+' && i != 0) ||
			    (status[i] < '0' || status[i] > '9'))
			{
				err = true;
				break;
			}
		if (i > 11)
			err = true;
		if (!err)
			value = _atoi(status);
		if (value < 0 || value > INT_MAX || err)
		{
			write(2, ferror, _strlen(ferror));
			write(2, "\n", 2);
			// call error writing function
			// sh: line: exit: Illegal number: status
			return (2);
		}
	}

	flags.exit = true;
	record_history(NULL, 0);
	// call any other functions that require cleanup

	global.exit_status = value & 0377;
	return (0);
}
