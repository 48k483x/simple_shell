# include "simple.h"
void signal_handler(int sig) {
    // Clear the screen
    system("/usr/bin/clear");
    printf("$ ");
    fflush(stdout);
}

void exit_message(int err_no, char *line) {
    perror("Error");
    free(line);
    exit(err_no);
}

int main(int ac, char **av) {
    (void) ac;
    (void) av;
    if (isatty(0)) {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        pid_t pid;

        signal(SIGINT, signal_handler);
        while (1) {
            printf("$ ");
            fflush(stdout);
            read = getline(&line, &len, stdin);
            if (read == -1)
                exit_message(12, line);
            if (read > 0 && line[read - 1] == '\n')
                line[read - 1] = '\0';
            if (strcmp(line, "exit") == 0)
                exit_message(0, line);
            else {
                char *args[BUFSIZ];
                char *token = strtok(line, " ");
                int i = 0;
                while (token != NULL) {
                    args[i++] = token;
                    token = strtok(NULL, " ");
                }
                args[i] = NULL;

                pid = fork();
                if (pid == -1)
                    exit_message(12, line);
                else if (pid == 0) {
                    if (execvp(args[0], args) == -1)
                        exit_message(2, line);
                } else
                    waitpid(pid, NULL, 0);
            }
        }
    }
    return 0;
}
