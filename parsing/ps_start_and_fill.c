/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_start_and_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:09:15 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/20 17:08:31 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_find_fill(t_shell *cmd, char *str, int i)
{
	int	start;

	while (str[i] == ' ')
		i++;
	start = i;
	while (str[i])
	{
		if ((str[i] == DOUBLEQ || str[i] == SINGLEQ) && ++i)
		{
			while ((str[i] != DOUBLEQ && str[i] != SINGLEQ) && str[i])
				i++;
			while (str[i] != ' ' && str[i])
				i++;
			break ;
		}
		else if (str[i] != ' ' && str[i])
			i++;
		else
			break ;
	}
	if (!ft_print_s(str[i]))
	{
		cmd->cmd = quote_remover(ft_substr(str, start, i - start), 0, 0);
		empty_maker(str, ' ', start, i - start);
	}
}

int	spaf_extras(t_shell *cmd, char **pipe_cmd, int i, t_rdr *listsize)
{
	cmd->org_rdr = ft_strdup(pipe_cmd[i]);
	if (check_redirect(pipe_cmd[i]))
	{
		if (heredoc_append_control(pipe_cmd[i], 0) == -1 \
			|| input_output_control(pipe_cmd[i], 0) == -1)
			return (free(cmd->org_rdr), -1);
		redirect_find_fill(cmd, pipe_cmd[i], 0, listsize);
	}
	cmd_find_fill(cmd, pipe_cmd[i], 0);
	args_find_fill(cmd, pipe_cmd[i]);
	make_empty(pipe_cmd[i], -1);
	return (0);
}

int	checkall(t_rdr *listsize, char **pipe_cmd, int i)
{
	int	j;

	j = i;
	while (listsize->listsize > j)
	{
		if (check_redirect(pipe_cmd[j]))
			if (heredoc_append_control(pipe_cmd[j], 0) == -1 \
				|| input_output_control(pipe_cmd[j], 0) == -1)
				return (free_double_ptr(pipe_cmd), -1);
		j++;
	}
	return (0);
}

int	split_pipe_and_fill(t_shell *cmd, char *str, int i, t_rdr *listsize)
{
	char	**pipe_cmd;
	t_shell	*temp;

	pipe_cmd = ft_split(str, PIPE);
	listsize->listsize = ft_strplen(pipe_cmd);
	if (checkall(listsize, pipe_cmd, 0) == -1)
		return (-1);
	temp = cmd;
	while (listsize->listsize > i)
	{
		if (spaf_extras(cmd, pipe_cmd, i, listsize) == -1)
			return (free_double_ptr(pipe_cmd), -1);
		if (i == listsize->listsize -1)
		{
			cmd->next = NULL;
			break ;
		}
		cmd->next = malloc(sizeof(t_shell));
		cmd = cmd->next;
		i++;
		struct_initializer(cmd);
	}
	free_double_ptr(pipe_cmd);
	cmd = temp;
	return (0);
}

int	single_cmd_fill(t_shell *cmd, char *str, t_rdr *list)
{
	char	*dist_str;

	dist_str = ft_strdup(str);
	cmd->org_rdr = ft_strdup(dist_str);
	if (check_redirect(str))
	{
		if ((heredoc_append_control(dist_str, 0) == -1 \
			|| input_output_control(dist_str, 0) == -1))
			return (free(dist_str), free(cmd->org_rdr), -1);
		redirect_find_fill(cmd, dist_str, 0, list);
	}
	cmd_find_fill(cmd, dist_str, 0);
	args_find_fill(cmd, dist_str);
	make_empty(dist_str, -1);
	free(dist_str);
	cmd->next = NULL;
	return (0);
}
