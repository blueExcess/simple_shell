/* super basic shell - starting point we can build off (using std functions) */
#include "basicshell.h"

/**
 * main - main for simple shell
 * @ac: number of arguments
 * @av: array of pointers to strings containing arguments passed
 * @env: environmental vars being passed to shell
 *
 * Return: status
 */
int main(int ac, char *av[], char **env)
{
	char *line = NULL, *exit = "exit\n", *cd = "cd\n", **token, *del = ' ';
	size_t len = 0;
	ssize_t actual;
	static char *prompt = "($) ";
	pid_t parent_pid;

	/* startup process */
	flags.startup = true;
	record_history(line, len);
	flags.startup = false;

	if (isatty(STDOUT_FILENO) == 1 && (isatty(STDIN_FILENO) == 1))
		flags.interactive = 1;

	do {
		write(1, prompt, 4);
		actual = getline(&line, &len, stdin);
		if (strcmp(line, exit) == 0)
		        flags.exit = true;
		record_history(line, actual);
		token = parser(line, del);
		/* pass token to search */

		free(line);
		line = NULL;
		len = 0;
	} while (flags.exit == false);
	return (0);
}

/**
 * record_history - records all input to the program and write out to perm file
 * @input: input from getline()
 * @len: num of bytes read by getline()
 *
 * Return: VOID
 */
void record_history(char *input, ssize_t len)
{
	static int file_tmp;
	int file_perm;
	static size_t written_total;
	ssize_t bytes_written, bytes_read, perm_br, perm_bw;
	char buffer[524288];
	char *temp = "/tmp/simple_shell_tmp_history";
	char *path = "/home/vagrant/.simple_shell_history";

/* startup - empty tmp file */
	if (flags.startup)
	{
		file_tmp = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 00666);
		if (file_tmp < 0)
			return;
		close(file_tmp);
		file_tmp = open(temp, O_WRONLY, 00666);
		if (file_tmp < 0)
			return;
/* set error flag? */
	}

	printf("line: %zd\n", len);
	bytes_written = write(file_tmp, input, len);
	if (bytes_written < 0)
		return;
	if ((size_t)bytes_written < len)
		return;
	written_total += bytes_written;
/* set error flag? */

/* on exit */
	if (flags.exit == true)
	{
		close(file_tmp);
		file_tmp = open(temp, O_RDONLY);
		file_perm = open(path, O_RDWR | O_CREAT | O_APPEND, 00666);
			if (file_perm < 0)
				return;
		/* need read/write function to avoid massive buffer sizes */
			printf("bytes_read = %zd\n written_total = %zd\n", bytes_read, written_total);
		bytes_read = read(file_tmp, buffer, written_total);
		printf("bytes_read (after  read tmp) = %zd\n", bytes_read);
		/* append perm file size to 4096 lines */
		perm_bw = write(file_perm, buffer, written_total);
		printf("perm_bw = %zd\n", perm_bw);
		close(file_tmp);
		close(file_perm);
	}
}
