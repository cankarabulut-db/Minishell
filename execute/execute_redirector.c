#include "../minishell.h"

void setup_input_redirection(t_shell *cmd)
{

		if (!cmd->fd_error)
        	cmd->ifd = open(cmd->input[cmd->cur_i++], O_RDONLY);
        if (cmd->ifd < 0)
        {
			cmd->fd_error = 1;
            perror("Error opening input file");
            return ;
        }
        if (dup2(cmd->ifd, STDIN_FILENO) < 0)
        {
            perror("dup2 input");
            exit(EXIT_FAILURE);
        }
        close(cmd->ifd);
}

void setup_output_redirection(t_shell *cmd)
{
		if (!cmd->fd_error)
        	cmd->ofd = open(cmd->output[cmd->cur_o++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (cmd->ofd < 0)
        {
			cmd->fd_error = 1;
            perror("Error opening output file");
            return ;
        }
        if (dup2(cmd->ofd, STDOUT_FILENO) < 0)
        {
            perror("dup2 output");
            exit(EXIT_FAILURE);
        }
        close(cmd->ofd);

}

void setup_append_redirection(t_shell *cmd)
{
		if (!cmd->fd_error)
        	cmd->ofd = open(cmd->append[cmd->cur_ap++], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (cmd->ofd < 0)
        {
			cmd->fd_error = 1;
            perror("Error opening append file");//bash deki hata çıktılarını kontrol edin.
            return; // buradan exit kalkacak yerine return atın ve diğer dosyalara dair işlem sonlanmalı. Örnek : ls > a > b > c için b dosyasında bir sorun olursa c dosyası oluşturulmamalı ve komut çalışmamalı
        }
        if (dup2(cmd->ofd, STDOUT_FILENO) < 0)
        {
            perror("dup2 append");
            exit(EXIT_FAILURE);
        }
        close(cmd->ofd);
}

void setup_redirections(t_shell *cmd)
{
	int i = -1;

	while (cmd->org_rdr[++i])
	{
		if (cmd->org_rdr[i] == OUTPUT)
		{
			setup_output_redirection(cmd);
		}
		else if(cmd->org_rdr[i] == INPUT && ++i)
			setup_input_redirection(cmd);
		else if(cmd->org_rdr[i] == APPEND && ++i)
			setup_append_redirection(cmd);
	}

    //setup_input_redirection(cmd);
	//if (cmd->status1 == OUTPUT)
	//{
    //	setup_append_redirection(cmd);
    //	setup_output_redirection(cmd);
	//}
	//if (cmd->status1 == APPEND)
	//{
    //	setup_output_redirection(cmd);
    //	setup_append_redirection(cmd);
	//}
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
