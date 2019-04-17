#include "basicshell.h"

/**
 * _strtostr - copy a string from source to destination
 * @source: string to copy
 * @dest: where to copy to
 *
 * Return: VOID
 */
6void _strtostr(char *source, char *dest)
{
	int i;

	if (source == NULL || dest == NULL)
		return;
	for (i = 0; source[i]; i++)
		dest[i] = source[i];
}

/**
 * _strchr - sets pointer to first occurrence of of c in str
 * @str: string to check
 * @c: character
 *
 * Return: pointer on success, NULL on failure. \0 is valid/included.
 */
7char *_strchr(char *str, int c)
{
/* NOTE: if '\0' is specified, will return pointer to NULL char at */
/* end of string (s + strlen(s)) */
	char *ptr = str;

	if (str == NULL)
		return (NULL);
	if (c == 0)
		return (ptr + _strlen(ptr));
	for (; *ptr; ptr++)
		if (*ptr == c)
			return (ptr);
	return (NULL);
}

/**
 * nl_cleaner - removes all nl from string
 * @str: string to clean
 *
 * Return: VOID
 */
8void nl_cleaner(char *str)
{
	char *hunter = str, *mover = str;
	int max_length, i;
	bool nl;

	if (str == NULL)
		return;
	if (*str == '\0')
		return;
	do {
		i = 0;
		nl = false;
		max_length = _strlen(hunter);
		hunter = str;
		for (; *hunter != '\n' && *mover; hunter++, i++)
		{
			nl = true;
			mover = hunter + 1;
			for (; *mover; i++, hunter++, mover++)
			{
				*hunter = *mover;
				printf("i: %d\n", i);
			}
		}
	} while (nl == true);
}

/**
 * nl_remover - remove newlines from string
 * @str: string to clense
 *
 * Return: VOID
 */
9void nl_remover(char *str)
{
	char *finder, *dest;
	char remove = '\n';

	for (finder = dest = str; *finder != '\0'; finder++)
	{
		*dest = *finder;
		if (*dest != remove)
			dest++;
	}
	*dest = '\0';
}

/**
 * _strcat - concatonate two strings
 * @dest: destination for concatination
 * @src: string to add
 *
 * Return: pointer to dest string
 */
10char *_strcat(char *dest, char *src)
{
	int i, x;

	i = x = 0;
	if (src == NULL)
		return (dest);
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[x] != '\0')
	{
		dest[i++] = src[x++];
	}
	dest[i] = '\0';
	return (dest);
}
