/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/20 15:50:46 by nkarabul         ###   ########.fr       */
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
	int		fd[2];
	int		cmdcount;
	t_shell	*temp;

	temp = cmd;
	cmdcount = cmd_counter(cmd);
	fd[0] = dup(0);
	fd[1] = dup(1);
	while (cmd)
	{
		if (cmd->next)
			pipe_exec(cmd);
		else
			one_cmd_2(cmd, cmdcount);
		if (cmd->next)
			cmd->next->env = cmd->env;
		cmd = cmd->next;
	}
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	cmd = temp;
	wait_childs(cmd, cmdcount);
	cmd = temp;
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
