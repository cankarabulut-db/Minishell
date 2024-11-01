#include "../minishell.h"

void setup_input_redirection(t_shell *cmd)
{
    int i;
    int fd;

    i = 0;
    while (cmd->input && cmd->input[i])
    {
        fd = open(cmd->input[i], O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2 input");
            exit(EXIT_FAILURE);
        }
        close(fd);
        i++;
    }
}

void setup_output_redirection(t_shell *cmd)
{
    int i;
    int fd;

    i = 0;
    while (cmd->output && cmd->output[i])
    {
        fd = open(cmd->output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2 output");
            exit(EXIT_FAILURE);
        }
        close(fd);
        i++;
    }
}

void setup_append_redirection(t_shell *cmd)
{
    int i;
    int fd;

    i = 0;
    while (cmd->append && cmd->append[i])
    {
        fd = open(cmd->append[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
            perror("Error opening append file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2 append");
            exit(EXIT_FAILURE);
        }
        close(fd);
        i++;
    }
}

void setup_redirections(t_shell *cmd)
{
    setup_input_redirection(cmd);
    setup_output_redirection(cmd);
    setup_append_redirection(cmd);
}


void process_heredoc_entry(int *fd)
{
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void read_heredoc_input(int fd)
{
    char *input_line = NULL;
    size_t len = 0;

    while (getline(&input_line, &len, stdin) != -1)
    {
        if (strcmp(input_line, "EOF\n") == 0)
            break;
        write(fd, input_line, strlen(input_line));
    }
    free(input_line);
}

void process_heredoc(t_shell *cmd)
{
    int i;
    int fd[2];

    i = 0;
    while (cmd->heredoc && cmd->heredoc[i])
    {
        process_heredoc_entry(fd);
        read_heredoc_input(fd[1]);
        close(fd[1]);

        if (dup2(fd[0], STDIN_FILENO) < 0)
        {
            perror("dup2 heredoc");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);
        i++;
    }
}
