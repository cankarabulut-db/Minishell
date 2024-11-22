/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/22 13:43:08 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_structs(t_shell *cmd)
{
	t_shell	*temp;
	t_shell	*temp2;

	free_structs_var(cmd);
	temp = cmd->next;
	while (temp)
	{
		temp2 = temp;
		free_structs_var(temp);
		temp = temp->next;
		free(temp2);
	}
}

void	start_cmd_part3(t_shell *cmd)
{
	t_shell	*temp;
	int		fd[2];
	int		cmdcount;
	int		heredoc_x;

	temp = cmd;
	cmdcount = cmd_counter(cmd);
	duplicate_open_close(fd, 1);
	heredoc_x = 0;
	while (cmd)
	{
		if (heredoc_x == 0)
			heredoc_check(cmd, fd);
		if (cmd->next)
			pipe_exec(cmd);
		else
			one_cmd_2(cmd, cmdcount);
		if (cmd->next)
			cmd->next->env = cmd->env;
		heredoc_x++;
		cmd = cmd->next;
	}
	duplicate_open_close(fd, 2);
	cmd = temp;
	wait_childs(cmd, cmdcount);
}

void	heredoc_check(t_shell *shell, int fd[2])
{
	t_shell	*temp;

	temp = shell;
	while (shell)
	{
		if (shell->heredoc && shell->heredoc[0])
			heredoc_init(shell, fd);
		shell = shell->next;
	}
	shell = temp;
}

void	start_cmd(char **env)
{
	t_shell	cmd;
	char	*temp;
	char	*rcmd;

	start_cmd_part1(&cmd, env);
	while (1)
	{
		struct_initializer(&cmd);
		start_cmd_part2(&cmd, &rcmd, &temp);
		if (!rcmd || ft_strlen(rcmd) == 0)
		{
			free(rcmd);
			free(temp);
			continue ;
		}
		if (start_parse(temp, &cmd) != -1)
		{
			join_cmd_arg(&cmd);
			start_cmd_part3(&cmd);
			free_structs(&cmd);
		}
		free(temp);
		free(rcmd);
	}
}

int	main(int ac, char *av[], char **env)
{
	(void)av;
	if (ac != 1)
	{
		error_msg(99);
		return (1);
	}
	set_signal(MAIN_P);
	start_cmd(env);
	return (0);
}
