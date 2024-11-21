/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:06:51 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/21 15:50:45 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_cmd_part1(t_shell *cmd, char **env)
{
	load_env_vars(cmd, env);
}

void	start_cmd_part2(t_shell *cmd, char **rcmd, char **temp)
{
	(void)cmd;
	*rcmd = readline("~minishell->");
	if (!*rcmd)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	add_history(*rcmd);
	tab_to_space(*rcmd, -1);
	*temp = ft_strtrim(*rcmd, " ");
}

void	pipe_exec(t_shell *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe error\n");
		exit(127);
	}
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
			exit(1);
		one_cmd(cmd);
		exit(127);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	wait_childs(t_shell *cmd, int i)
{
	int		status;
	t_shell	*temp;
	pid_t	j;

	if (i == 1 && is_builtin(cmd->cmd))
		return ;
	temp = cmd;
	while (cmd)
	{
		signal(SIGINT, &handle_sigint);
		j = waitpid(cmd->pid, &status, 0);
		if (j < 0)
			continue ;
		if (WIFEXITED(status))
			g_global_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global_exit = 128 + WTERMSIG(status);
		cmd = cmd->next;
	}
	cmd = temp;
}

int	cmd_counter(t_shell *cmd)
{
	t_shell	*temp;
	int		i;

	i = 0;
	temp = cmd;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	cmd = temp;
	return (i);
}
