/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:06:58 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:15:35 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_cmd_arg_part2(t_shell *mini, int *i)
{
	while (mini->args[*i - 1])
	{
		mini->execve_args[*i] = ft_strdup(mini->args[*i - 1]);
		(*i)++;
	}
	mini->execve_args[*i] = NULL;
}

void	join_cmd_arg(t_shell *mini)
{
	int		arg_c;
	int		i;
	t_shell	*temp;

	temp = mini;
	while (mini)
	{
		join_cmd_arg_part1(mini, &arg_c, &i);
		join_cmd_arg_part2(mini, &i);
		mini = mini->next;
	}
	mini = temp;
}

void	join_cmd_arg_part1(t_shell *mini, int *arg_c, int *i)
{
	*arg_c = ft_strplen(mini->args);
	mini->execve_args = malloc(sizeof(char *) * (*arg_c + 2));
	mini->execve_args[0] = ft_strdup(mini->cmd);
	*i = 1;
}

void	free_structs_var(t_shell *cmd)
{
	if (cmd->input)
		free_double_ptr(cmd->input);
	if (cmd->append)
		free_double_ptr(cmd->append);
	if (cmd->output)
		free_double_ptr(cmd->output);
	if (cmd->heredoc)
		free_double_ptr(cmd->heredoc);
	if (cmd->args)
		free_double_ptr(cmd->args);
	if (cmd->org_rdr)
		free(cmd->org_rdr);
	if (cmd->execve_args)
		free_double_ptr(cmd->execve_args);
	if (cmd->cmd)
		free(cmd->cmd);
}
