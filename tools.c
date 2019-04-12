/* helper functions */
#include "simpleshell.h"

/* word count */
unsigned int _wordCount(char *str)
{
	char *delim = "\n \t";
	unsigned int wrdCnt, index, flag;

	index = 0;
	flag = 0;
	wrdCnt = 1;

	for (; str[index]; index++)
	{
		if (flag == 0 &&
		    (str[index] == delim[0]
		     || str[index] == delim[1]
		     || str[index] == delim[2])
		    && str[index + 1] != delim[0]
		    && str[index + 1] != delim[1]
		    && str[index + 1] != delim[2])
		{
			flag = 1;
			wrdCnt++;
		}
		else
		{
			flag = 0;
		}
	}
	return (wrdCnt);
}

/* string compare */
int _strcmp(char *s1, char *s2)
{
	int index = 0;

	while (s1[index] != '\0' && s2[index] != '\0')
	{
		if (s1[index] != s2[index])
		{
			return ((s1[index] - '0') - (s2[index] - '0'));
		}
		index++;
	}
	return (0);
}

/**
 * _strlen - get length of string
 * @str: string to check
 *
 * Return: length of string, -1 on fail
 */
int _strlen(char *str)
{
	int count = 0;

	if (str == NULL)
		return (-1);
	for (; str[count]; count++)
		;
	return (count);
}
/**
 * _astrlen - returns length of every string in array of pointers to strings
 * @str: array of pointers to strings to get length of
 *
 * Return: an array of lengths of strings, arr[0] = len of new array;
 */
int *_astrlen(char **str)
{
	static int arr[1024];
	int i, j, x;

	if (str == NULL || *str == NULL)
		return (NULL);
	/* how many pointers in array */
	for (x = 0; str[x]; x++)
		;
	arr[0] = x;
	for (i = 0; str[i - 1]; i++)
	{
		for (j = 0; str[i][j]; j++)
			;
		arr[i + 1] = j;
	}

	return (arr);
}

/**
 * _strcpy - copy a string from source to location
 * @source: string to copy
 * @extra: how many extra bytes to include after end of string
 *
 * Return: pointer to begining of null-term string.
 */
char *_strcpy(char *source, unsigned int extra)
{
	char *copy;
	int i;

	if (source == NULL)
		return (NULL);
	for (i = 0; source[i]; i++)
		;
	copy = malloc(sizeof(char) * i + 1 + extra);
	if (copy == NULL)
		return (NULL);
	for (i = 0; source[i]; i++)
		copy[i] = source[i];
	copy[i + extra] = '\0';

	return(copy);
}

/**
 * _strtostr - copy a string from source to destination
 * @source: string to copy
 * @dest: where to copy to
 *
 * Return: VOID
 */
void _strtostr(char *source, char *dest)
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
char *_strchr(char *str, int c)
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
void nl_cleaner(char *str)
{
	char *hunter = str, *mover = str;
	int max_length, i;
	bool nl;

	printf("entered scrubber\n"); // debug
	if (str == NULL)
		return;
	if (*str == '\0')
		return;
	printf("(scrubber) string: %s\n", str); // debug
	do{
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
			printf("ml: %d, i: %d\n", max_length, i); // debug
		}
	} while (nl == true);
	printf("(post scrubber) string: %s\n", str); // debug
}

void nl_remover(char *str)
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
