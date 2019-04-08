/* super basic shell - starting point we can build off (using std functions) */
#include "basicshell.h"


int main(int ac, char *av[], char **env)
{
	char *line = NULL, *exit = "exit\n", *cd = "cd\n";
	size_t len = 0;
	static char *prompt = "($) ";
	pid_t parent_pid;

	/* startup process */
	record_history(line, len);
	F_STARTUP = false;

	do {
	write(1, prompt, 4);
	getline(&line, &len, stdin);
	if (strcmp(line, exit) == 0)
		F_EXIT = true;
	record_history(line, len, startup);
	/* pass line to parser */
	/* free(line); */
	} while (F_EXIT == false);
	free(line);
	return (0);
}


void record_history(char *input, size_t len)
{
	int file_tmp, file_perm, bw = 0;
	static size_t written_total = 0;
	ssize_t bytes_written, bytes_read, perm_br;
	size_t written_total = 0;
	char buffer[524288];
	char *temp = "/tmp/simple_shell_tmp_history";
	char *path = "/home/vagrant/.simple_shell_history";

/* startup - empty tmp file */
	if (F_STARTUP)
	{
		file_tmp = open(temp, O_WRONLY | O_CREAT| O_TRUNC, 00666);
		if (file_tmp < 0)
			return;
		close(file_tmp);
		file_tmp = open(temp, O_WRONLY | O_APPEND, 00666);
		if (file_tmp < 0)
			return;
/* set error flag? */
	}
	if (len > 0)
	{
		bytes_written = write(file_tmp, input, len);
		bytes_written = bw;
		if (bw < len)
			return;
		written_total += bytes_read;
/* set error flag? */
	}
/* on exit */
	if (F_EXIT == true)
	{
		close(file_tmp);
		file_tmp = open(temp, O_RDWR);
		file_perm = open(path, O_RDWR | O_CREAT | O_APPEND, 00666);
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
