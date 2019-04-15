/* helper functions */
#include "simpleshell.h"

/* word count */
unsigned int _wordCount(char *str)
{
	char *delim = "\n \t :";
	unsigned int wrdCnt, index, flag;

	index = 0;
	flag = 0;
	wrdCnt = 1;

	for (; str[index]; index++)
	{
		if (flag == 0 &&
		    (str[index] == delim[0]
		     || str[index] == delim[1]
		     || str[index] == delim[2]
		     || str[index] == delim[3]
		     || str[index] == delim[4])
		    && str[index + 1] != delim[0]
		    && str[index + 1] != delim[1]
		    && str[index + 1] != delim[2]
		    && str[index + 1] != delim[3]
		    && str[index + 1] != delim[4])
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
	for (i = 0; str[i]; i++)
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
char *_strdup(char *source, unsigned int extra)
{
	char *copy;
	int i;

	puts("(strdup) entry"); // debug
	if (source == NULL)
		return (NULL);
	printf("(strdup) source: %s, len: %zd\n", source, strlen(source)); // debug
	puts("(strdup) check 1"); // debug
	for (i = 0; source[i]; i++)
		;
	puts("(strdup) check 2"); // debug
	copy = malloc(sizeof(char) * i + extra + 1);
	puts("(strdup) check 3"); // debug
	if (copy == NULL)
		return (NULL);
	puts("(strdup) check 4"); // debug
	for (i = 0; source[i]; i++)
		copy[i] = source[i];
	puts("(strdup) check 5"); // debug
	copy[i] = '\0';
	puts("(strdup) check 6"); // debug
	if (extra > 0)
	{
		i++;
		puts("(strdup) check 7"); // debug
		for (extra += i; i < extra; i++)
			copy[i] = '\0';
		puts("(strdup) check 8"); // debug
	}

	puts("(strdup) check 9"); // debug
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

/**
 * nl_remover - remove newlines from string
 * @str: string to clense
 *
 * Return: VOID
 */
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

/**
 * _strcat - concatonate two strings
 * @dest: destination for concatination
 * @src: string to add
 *
 * Return: pointer to dest string
 */
char *_strcat(char *dest, char *src)
{
	int i, x;

	i = x = 0;

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
void updateDir(char *directory, char *beginning)
{
	int length, index = 0, count = 0;
	char *printDir;

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
	while (__environ[index])
	{
		if (strncmp(beginning, __environ[index++], length) == 0)
		{
			__environ[index] = printDir;
			break;
		}
		index++;
	}
}

char *cpyPath(char *input)
{
	int index = 0, length = 0;
	char *dest;

	length = _strlen(input);
	while (__environ[index])
	{
		if (strncmp(input, __environ[index], length) == 0)
		{
			dest = __environ[index];
			break;
		}
		index++;
	}
	dest = dest + length;

	return (dest);
}
