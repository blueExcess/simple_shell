/* super basic shell - starting point we can build off (using std functions) */
#include "simpleshell.h"

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
	char *line = NULL, **token, *del = " ", *path = NULL;
	size_t len = 0;
	ssize_t actual;
	int btest;

	startup(ac, av);
	namesave(av);

	do {
		print_prompt();
		actual = getline(&line, &len, stdin);
		global.line_no++;
		record_history(line, actual);
		nl_remover(line);
		if (actual == -1)
		{
			if (flags.interactive)
				write(STDERR_FILENO, "\n", 1);
			break;
		}
		if (*line == '\0')
			continue;
		if (double_space_remover(line) == 0)
			continue;
		token = parser(line, del);
		btest = search_builtins(token);
		if (btest == 1)
		{
			path = path_finder(env);
			fork_exec(path, token, env);
		}
		free(path);
		free(line);
		line = NULL;
		len = 0;
		global.command = NULL;
		free(global.command);
	} while (flags.exit == false);
	return (global.exit_status);
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
	ssize_t bytes_written;
	char buffer[524288];
	char *temp = "/tmp/simple_shell_tmp_history";
	char *path = "/home/vagrant/.simple_shell_history";

	if (flags.startup)
	{
		file_tmp = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 00666);
		if (file_tmp < 0)
			return;
		close(file_tmp);
		file_tmp = open(temp, O_WRONLY, 00666);
		if (file_tmp < 0)
			return;
	}

	bytes_written = write(file_tmp, input, len);
	if (bytes_written < 0)
		return;
	if ((ssize_t)bytes_written < len)
		return;
	written_total += bytes_written;
	if (flags.exit == true)
	{
		close(file_tmp);
		file_tmp = open(temp, O_RDONLY);
		file_perm = open(path, O_RDWR | O_CREAT | O_APPEND, 00666);
		if (file_perm < 0)
			return;
		read(file_tmp, buffer, written_total);
		write(file_perm, buffer, written_total);
		close(file_tmp);
		close(file_perm);
	}
}


/**
 * print_prompt - if interactive mode, print prompt to stderr, else no prompt
 *
 * Return: VOID
 */
void print_prompt(void)
{
	static char *prompt = "$ ";

	if (flags.interactive == true)
		write(STDERR_FILENO, prompt, 3);
}

/**
 * startup - run all shell startup proscesses
 * @ac: argument count
 * @av: argument list
 * Return: VOID
 */
void startup(int ac, char **av)
{
	/* set startup flag */
	flags.startup = true;

/* may end up tx startup sequences of functions here */
	if (ac > 1)
		global.input = open(av[1], O_RDONLY);
	else
		global.input = STDIN_FILENO;

	if (isatty(STDOUT_FILENO) == 1 && isatty(global.input) == 1)
	{
		flags.interactive = true;
		signal(SIGINT, &sig_handler);
	}

/* set up record keeping */
	record_history(NULL, 0);

	/* unset startup flag */
	flags.startup = false;
}

/**
 * sig_handler - stops ctrl+c from exiting shell
 * @n: is the actual command coming in from the OS signal
 */

void sig_handler(int n __attribute__((unused)))
{
	char *prompt = "\n$ ";

	write(STDERR_FILENO, prompt, 5);
}
