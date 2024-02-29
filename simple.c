#include "simple.h"

/*
 * This is a simple shell program that implements basic shell functionalities.
 * It allows users to execute commands, change directories, and handle process management.
 * The program uses various system calls and library functions to achieve these functionalities.
 * Allowed functions include:
 *			access() chdir() close() closedir() execve() exit() _exit() fflush() fork() free() getcwd() getline() getpid() isatty()
 * 			kill() malloc() open() opendir() perror() read() readdir() signal() stat() lstat() fstatt() strtok() wait() waitpid() 
 * 			wait3() wait4()  write()
 */

char *exit_message(int err_no, char *line)
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
