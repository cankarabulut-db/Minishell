/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:44:43 by akar              #+#    #+#             */
/*   Updated: 2024/11/19 15:32:51 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fderror(char *str)
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
void setup_heredoc_redirection(t_shell *cmd)
{
	(void)cmd;
	printf("setupheredoc\n");
}

void	setup_redirections(t_shell *cmd)
{
	int	i;

	i = -1;
	while (cmd->org_rdr[++i])
	{
		if (cmd->fd_error)
			break ;
		if (cmd->org_rdr[i] == OUTPUT)
			setup_output_redirection(cmd);
		else if (cmd->org_rdr[i] == INPUT && ++i)
			setup_input_redirection(cmd);
		else if (cmd->org_rdr[i] == APPEND && ++i)
			setup_append_redirection(cmd);
		else if(cmd->org_rdr[i] == HEREDOC && ++i)
			setup_heredoc_redirection(cmd);
	}
	cmd->cur_ap = 0;
	cmd->cur_i = 0;
	cmd->cur_o = 0;
}

void	process_heredoc_entry(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	read_heredoc_input(int fd)
{
	char	*input_line;
	size_t	len;

	len = 0;
	input_line = NULL;
	while (getline(&input_line, &len, stdin) != -1)
	{
		if (strcmp(input_line, "EOF\n") == 0)
			break ;
		write(fd, input_line, ft_strlen(input_line));
	}
	free(input_line);
}

void	process_heredoc(t_shell *cmd)
{
	int	i;
	int	fd[2];

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
