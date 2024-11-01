#include "../minishell.h"

void execute_piped_commands(t_shell *cmd) {
    int pipefd[2];
    pid_t pid;
    int in_fd = 0; 

    while (cmd) {
        if (cmd->next) { 
            if (pipe(pipefd) == -1) {
                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
        }

        if ((pid = fork()) == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { 
            if (in_fd != 0) {
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (cmd->next) {
                close(pipefd[0]);
                dup2(pipefd[1], 1);
                close(pipefd[1]);
            }
            execve(cmd->cmd, cmd->execve_args, cmd->env);
            perror("execve failed");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, NULL, 0); 
            close(pipefd[1]);
            in_fd = pipefd[0];
            cmd = cmd->next;
        }
    }
}
