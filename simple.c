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
			printf("shhh> ");
			fflush(stdout);
			read = getline(&line, &len, stdin);
			if (read == -1)
			{
				perror("getline");
				exit(1);
			}
			if (strcmp(line, "exit\n") == 0)
			{
				free(line);
				exit(0);
			}
			else
			{
				pid = fork();
				if (pid == -1)
				{
					perror("fork");
					exit(1);
				}
				else if (pid == 0)
				{
					char *program = strtok(line, " ");
					char *arg = strtok(NULL, " ");
					char *args[] = {program, arg, NULL};
					execvp(args[0], args);
				}
			}
		}
	}
}