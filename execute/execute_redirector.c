/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:44:43 by akar              #+#    #+#             */
/*   Updated: 2024/11/12 21:09:00 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void fderror(char *str)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (is_directory(str))
		ft_putstr_fd(": Is a directory\n", 2);
	else if (!is_file(str))
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (access(str, R_OK))
		ft_putstr_fd(": Permission denied\n", 2);
	g_global_exit = 1;
}
void setup_input_redirection(t_shell *cmd)
{
        if (!cmd->fd_error && !cmd->input && !cmd->input[cmd->cur_i])
            return ;
		if (!cmd->fd_error && cmd->input && cmd->input[cmd->cur_i])
        	cmd->ifd = open(cmd->input[cmd->cur_i++], O_RDONLY);
        if (cmd->ifd < 0)
        {
			cmd->fd_error = 1;
            fderror(cmd->input[cmd->cur_i - 1]);
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
        if (!cmd->fd_error && !cmd->output[cmd->cur_o])
            return ;
		if (!cmd->fd_error)
        	cmd->ofd = open(cmd->output[cmd->cur_o++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (cmd->ofd < 0)
        {
			cmd->fd_error = 1;
            fderror(cmd->output[cmd->cur_o - 1]);
            return ;
        }
        if (dup2(cmd->ofd, STDOUT_FILENO) < 0)
            exit(EXIT_FAILURE);
        close(cmd->ofd);

}

void setup_append_redirection(t_shell *cmd)
{
        if (!cmd->fd_error && !cmd->append[cmd->cur_ap])
            return ;
		if (!cmd->fd_error)
        	cmd->ofd = open(cmd->append[cmd->cur_ap++], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (cmd->ofd < 0)
        {
			cmd->fd_error = 1;
            dprintf(2,"append: %s\n",cmd->append[cmd->cur_ap - 1]);
            fderror(cmd->append[cmd->cur_ap - 1]); //bash deki hata çıktılarını kontrol edin.
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
        if (cmd->fd_error)
            break;
		if (cmd->org_rdr[i] == OUTPUT)
			setup_output_redirection(cmd);
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
