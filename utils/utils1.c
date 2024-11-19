/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:07:10 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 14:32:31 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd(t_shell *cmd)
{
	int		path_index;
	char	*find_path;

	if (is_builtin(cmd->execve_args[0]))
	{
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
		{
			exit(1);
			return ;
		}
		execute_builtin(cmd->execve_args, cmd);
		return ;
	}
	path_index = get_path_index(cmd);
	find_path = find_executable_path(cmd, path_index);
	if (!find_path)
		exit(g_global_exit);
	execve(find_path, cmd->execve_args, cmd->env);
	exit(127);
}

void	oc2_child(t_shell *cmd, int cmdcount, int path_index)
{
	char	*find_path;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		find_path = find_executable_path(cmd, path_index);
		if (!find_path)
			exit(g_global_exit);
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
			exit(1);
		if (is_builtin(cmd->execve_args[0]) && cmdcount == 1)
		{
			execute_builtin(cmd->execve_args, cmd);
			exit(0);
		}
		execve(find_path, cmd->execve_args, cmd->env);
		exit(127);
	}
}

void	one_cmd_2(t_shell *cmd, int cmdcount)
{
	if (is_builtin(cmd->execve_args[0]) && cmdcount == 1)
	{
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
		{
			g_global_exit = 1;
			return ;
		}
		execute_builtin(cmd->execve_args, cmd);
		return ;
	}
	oc2_child(cmd, cmdcount, get_path_index(cmd));
}

void	struct_initializer(t_shell *cmd)
{
	cmd->cur_ap = 0;
	cmd->cur_i = 0;
	cmd->cur_o = 0;
	cmd->pid = 0;
	cmd->append = NULL;
	cmd->args = NULL;
	cmd->ifd = -1;
	cmd->ofd = -1;
	cmd->fd_error = 0;
	cmd->status = -1;
	cmd->status1 = -1;
	cmd->cmd = NULL;
	cmd->heredoc = NULL;
	cmd->input = NULL;
	cmd->main_env = NULL;
	cmd->next = NULL;
	cmd->output = NULL;
}

void	tab_to_space(char *str, int i)
{
	while (str[++i])
		if (str[i] == '\t')
			str[i] = 32;
}
