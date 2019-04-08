#include "basicshell.h"

/* word count */
unsigned int _wordCount(char *str)
{
	char *delim = "\n \t";
	unsigned int wrdCnt, index, flag;

	index = flag = 0;
	wrdCnt = 1;
	for (; str[index]; index++)
	{
		if (flag == 0 &&
		    (str[index] == delim[0]
		     || str[index] == delim[1]
		     || str[index] == delim[2])
		    && str[index++] != delim[0]
		    && str[index++] != delim[1]
		    && str[index++] != delim[2])
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

