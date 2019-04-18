/* error handling functions */
#include "simpleshell.h"

/**
 * basic_err - prints out argv[0] and line no
 *
 * Return: VOID
 */
void basic_err(void)
{
	char *line;


	line = _itoa(global.line_no);
	write(STDERR_FILENO, global.az, _strlen(global.az));
	write(STDERR_FILENO, line, _strlen(line));
	global.exit_status = errno;
	if (errno == EACCES)
		global.exit_status = 126;
	else if (errno == ENOENT)
		global.exit_status = 127;
	else
		global.exit_status = 2;

}

/**
 * std_err - calls perror
 *
 * Return: VOID
 */
void std_err(void)
{
	basic_err();
	perror(global.command);
	global.exit_status = errno;
	if (errno == EACCES)
		global.exit_status = 126;
	else if (errno == ENOENT)
		global.exit_status = 127;
	else
		global.exit_status = 2;
}


/**
 * namesave - saves argv[0] into a global for error printing
 * @av: argv
 *
 * Return: NULL
 */
void namesave(char **av)
{
	int x;

	x = _strlen(av[0]);
	global.az = malloc(sizeof(char) * x + 3);

	_strtostr(av[0], global.az);
	global.az[x] = ':';
	global.az[x + 1] = ' ';
	global.az[x + 2] = '\0';
}

/**
 * _itoa - change int to string
 * @x: number to convert
 *
 * Return: converted string
 */
char *_itoa(int x)
{
	static char str[14] = {'\0'};
	char *end, *beg = str, *temp, *ret;
	int i = 0;

	for (i = 0; i < 14; i++)
		str[i] = '\0';
	end = str;
	beg = str;
	i = 0;
	if (x == 0)
		str[0] = '0';
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x /= 10;
	}
	end = _strchr(str, '\0');
	end--;
	while (beg < end)
	{
		temp = beg;
		beg = end;
		end = temp;
		beg++, end--;
	}
	end = _strchr(str, '\0');
	str[i] = ':';
	str[i + 1] = ' ';
	str[i + 2] = '\0';
	ret = str;
	return (ret);
}
