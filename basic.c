/* super basic shell - starting point we can build off (using std functions) */
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "basicshell.h"

int main(int ac, char *av[],char **env)
{
	char *line = NULL, *exit = "exit\n", *cd = "cd\n";
	size_t len = 0;
	static char *prompt = "($) ";
	pid_t parent_pid;
	int startup = 1;

	/* startup process */
	record_history(line, len, startup);
	startup = 0;

	do {
	write(1, prompt, 4);
	getline(&line, &len, stdin);
	record_history(line, len, startup);
	/* pass line to parser */

	free(line);
	} while (strcmp(line, exit));
	free(line);
	return (0);
}


void record_history(char *input, size_t len, int startup)
{
	int file_tmp, file_perm, bw = 0;
	ssize_t bytes_written, bytes_read, perm_br;
	size_t written_total = 0;
	char buffer[524288];
	char *temp = "temp/simple_shell_tmp_history";
	char *path = "home/.simple_shell_history";

/* need line numbers in tmp - displayed by history cmd, removed for write to perm file */
/* need function to count number of lines - based on \n found */
/* startup - empty tmp file */
	if (startup)
	{
		file_tmp = open(temp, O_WRONLY | O_CREAT| O_TRUNC, 00666);
		if (file_tmp < 0)
			return;
		close(file_tmp);
	}

	file_tmp = open(temp, O_RDWR | O_CREAT | O_APPEND, 00666);
	if (file_tmp < 0)
		return;
/* set error flag? */
	if (len > 0)
	{
		bytes_written = write(file, input, len);
		bytes_written = bw;
		if (bw < len)
			return;
		written_total += bytes_read;
/* set error flag? */
	}
/* on exit */
	if (flags->exit)
	{
		file_perm = open(path, O_RDWR | O_CREAT | O_APPEND, 00666)
			if (file_perm < 0)
				return;
		/* need read/write function to avoid massive buffer sizes */
		bytes_read = read(file_tmp, buffer, written_total);
		/* append perm file size to 4096 lines */
		perm_bw = write(file_perm, buffer, written_total);
		close(file_tmp);
		close(file_perm);
	}
}
