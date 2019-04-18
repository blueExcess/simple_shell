#include "simpleshell.h"

/**
 * _atoi - convert letters to numbers
 * @str: string to convert to numbers
 *
 * Return: int
 */
long int _atoi(char *str)
{
	int i = 0, num = 0;

	if (str[0] == '+')
		i++;
	for (; str[i]; i++)
		if (str[i] >= '0' || str[i] <= '9')
			num = num * 10 + (str[i] - '0');

	return (num);
}

/**
 * fly_free - free arrays of pointers to strings
 * @str: thing to set free
 *
 * Return: VOID
 */
void fly_free(char **str)
{
	int i = 0;

	if (str == NULL || *str == NULL)
		return;
	for (; str[i]; i++)
		free(str[i]);
	free(str);
}
/**
 * updateDir - updates the directory
 * @directory: current directory
 * @beginning: directory to append on
 * Return: void
 */
void updateDir(char *directory, char *beginning)
{
	int length, index = 0, count = 0;
	char *printDir, **env;

	env = environ;

	length = _strlen(directory) + _strlen(beginning);
	printDir = malloc(sizeof(char) * length);

	for (index = 0; index < length; index++)
	{
		if (index < _strlen(beginning))
			printDir[index] = beginning[index];
		else
			printDir[index] = beginning[count++];
	}
	printDir[index] = '\0';
	index = 0;
	length = _strlen(beginning);
	while (env[index])
	{
		if (_strncmp(beginning, env[index++], length) == 0)
		{
			env[index] = printDir;
			break;
		}
		index++;
	}
}
/**
 * cpyPath - copies path from input to destination
 * @input: path/string input
 * Return: returns new destination and saves old PWD
 */
char *cpyPath(char *input)
{
	int index = 0, length = 0;
	char *dest, **env;

	env = environ;

	length = _strlen(input);
	while (env[index])
	{
		if (_strcmp(input, env[index]) == 0)
		{
			dest = env[index];
			break;
		}
		index++;
	}
	dest = dest + length;

	return (dest);
}

/**
 * _strncmp - compare two strings
 * @src: source (compare to)
 * @check: string to check
 * @num: num of bytes to check
 *
 * Return: 0 if match
 */
int _strncmp(char *src, char *check, int num)
{
	int i = 0;

	for (; src[i] && (src[i] == check[i]) && i < num - 1; i++)
		;
	if (src[i] == check[i])
		return (0);
	return (1);
}
