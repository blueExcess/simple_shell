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
