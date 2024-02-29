#include "simple.h"

char
exit_message(int err_no, char *line)
{
	perror("Error");
	free(line);
	exit(err_no);
}
int
main(int ac, char **av)
{
	(void) ac;
	(void) av;
	if (isatty(0))
	{
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
		pid_t pid;

		while (1)
		{
			printf("Shhhh> ");
			fflush(stdout);
			read = getline(&line, &len, stdin);
			if (read == -1)
				exit_message(12, line);
			if (read > 0 && line[read - 1] == '\n')
				line[read - 1] = '\0';
			if (strcmp(line, "exit") == 0)
				exit_message(0, line);
			else
			{
				pid = fork();
				if (pid == -1)
					exit_message(12, line);
				else if (pid == 0)
				{
					char *program = strtok(line, " ");
					char *arg = strtok(NULL, " ");
					char *args[] = {program, arg, NULL};

					if (execvp(args[0], args) == -1)
						exit_message(2, line);
				}
				else
						waitpid(pid, NULL, 0);
			}
		}
	}
}
