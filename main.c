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
	char *line = NULL, *exit = "exit\n", **token, *del = " ", *path;
	size_t len = 0;
	ssize_t actual;
	pid_t parent_pid;
	int btest;

	startup(ac, av);

	do {
		/* write(2, prompt, 4); */
		print_prompt();
		actual = getline(&line, &len, stdin);
		global.line_no++;
		record_history(line, actual);
		nl_remover(line);
		if (*line == '\0' || actual == -1) // better to do check in word count
			if (!flags.interactive)
				break;
			else
				continue;
		token = parser(line, del);
		btest = search_builtins(token);
		printf("(main) btest: %d\n", btest); // debug
		// call path_finder only if builtin returns 1 (not found)
		if (btest == 1)
		{
			path = path_finder(env);
			printf("(main) path: %s\n", path); // debug
			fork_exec(path, token, env); // arg1 to path when fixed
		}
		free(path); // need function to free all **x

		/*free(line); */
		line = NULL;
		len = 0;
		printf("(main) flags.exit: %d\n", flags.exit); // debug
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

	printf("(record_history) line: %zd\n", len); // debug
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


/**
 * prompt - if interactive mode, print prompt to stderr, else no prompt
 *
 * Return: VOID
 */
void print_prompt(void)
{
	static char *prompt = "($) ";

	if (flags.interactive == true)
		write(STDERR_FILENO, prompt, 4);
}

/**
 * startup - run all shell startup proscesses
 *
 * Return: VOID
 */
void startup(int ac, char **av)
{
	/* set startup flag */
	flags.startup = true;

/* may end up tx startup sequences of functions here */

// check if passed file to hsh
	if (ac > 1)
		global.input = open(av[1], O_RDONLY);
	else
		global.input = STDIN_FILENO;

// check if interactive
	if (isatty(STDOUT_FILENO) == 1 && isatty(global.input) == 1)
	{
		flags.interactive = true;
		signal(SIGINT, &sig_handler);
	}

//set up record keeping
	record_history(NULL, 0);

	/* unset startup flag */
	flags.startup = false;
}

/**
 * sig_handler - stops ctrl+c from exiting shell
 * @n: is the actual command coming in from the OS signal
 */

void sig_handler(int n)
{
	char *prompt = "\n($) ";

	write(STDERR_FILENO, prompt, 5);
}
