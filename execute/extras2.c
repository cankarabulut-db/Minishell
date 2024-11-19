/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:08:23 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 15:28:43 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	runcommanderror(char **command, int i)
{
	if (i == 0)
	{
		error_write(command[0]);
		ft_putendl_fd(": No such file or directory\n", 2);
		g_global_exit = 127;
		return (1);
	}
	else if (i == 1)
	{
		error_write(command[0]);
		ft_putendl_fd(": Permission denied", 2);
		g_global_exit = 126;
		return (1);
	}
	else if (i == 2)
	{
		error_write(command[0]);
		ft_putendl_fd(": is a directory", 2);
		g_global_exit = 126;
		return (1);
	}
	return (0);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISREG(path_stat.st_mode));
}

void	setup_input_redirection(t_shell *cmd)
{
	if (cmd->fd_error && !cmd->input && !cmd->input[cmd->cur_i])
		return ;
	cmd->ifd = open(cmd->input[cmd->cur_i], O_RDONLY);
	cmd->cur_i++;
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

void	setup_output_redirection(t_shell *cmd)
{
	if (!cmd->fd_error && !cmd->output && !cmd->output[cmd->cur_o])
		return ;
	if (!cmd->fd_error)
		cmd->ofd = open(cmd->output[cmd->cur_o++], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	setup_append_redirection(t_shell *cmd)
{
	if (!cmd->fd_error && !cmd->append && !cmd->append[cmd->cur_ap])
		return ;
	if (!cmd->fd_error)
		cmd->ofd = open(cmd->append[cmd->cur_ap++], \
					O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->ofd < 0)
	{
		cmd->fd_error = 1;
		fderror(cmd->append[cmd->cur_ap - 1]);
		return ;
	}
	if (dup2(cmd->ofd, STDOUT_FILENO) < 0)
	{
		perror("dup2 append");
		exit(EXIT_FAILURE);
	}
	close(cmd->ofd);
}
