/* super basic shell - starting point we can build off (using std functions) */
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *line = NULL, *exit = "exit\n";
	size_t len = 0;
	static char *prompt = "($) ";
	pid_t parent_pid;

	do {
	write(1, prompt, 4);
	getline(&line, &len, stdin);
	/* printf("value of *line is now: %s", line); */


	} while (strcmp(line, exit));
	return (0);
}
