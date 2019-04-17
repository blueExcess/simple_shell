/* error handling functions */
#include "simpleshell.h"

void basic_error(void)
{
	char *line;


	line = _itoa(global.line_no);
	printf("line: %s\n", line); // debug
	printf("az: %s\n", global.az); // debug
	write(STDERR_FILENO, global.az, _strlen(global.az));
	write(STDERR_FILENO, line, _strlen(line));
}

void std_err(void)
{
	basic_error();
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

char *_itoa(int x)
{
	char str[10] = {'\0'};
	char *end, *beg = str;
	int i = 0;

	if (x == 0)
		str[0] == '0';
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
	*end = ':';
	*(end + 1) = ' ';
	return (str);
}
