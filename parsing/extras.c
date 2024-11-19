/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:07:39 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 14:39:14 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_find_fill(t_shell *cmd, char *str, int i, t_rdr *rdrcount)
{
	rdr_makezero(rdrcount);
	redirect_malloc(cmd, str, rdrcount);
	redirect_fill_null(cmd, rdrcount);
	while (str[i])
	{
		if (str[i] == INPUT || str[i] == OUTPUT
			|| str[i] == APPEND || str[i] == HEREDOC)
		{
			rdrcount->type = str[i];
			if (rdrcount->type == APPEND || rdrcount->type == HEREDOC)
			{
				str[i] = ' ';
				str[i + 1] = ' ';
				i += 2;
			}
			else if (rdrcount->type == INPUT || rdrcount->type == OUTPUT)
				str[i++] = ' ';
			while (str[i] == ' ')
				i++;
			redirects_filler(cmd, str, rdrcount, i);
		}
		i++;
	}
}

void	redirect_fill_null(t_shell *cmd, t_rdr *rc)
{
	if (cmd->append)
		cmd->append[rc->ac] = NULL;
	if (cmd->heredoc)
		cmd->heredoc[rc->hc] = NULL;
	if (cmd->input)
		cmd->input[rc->ic] = NULL;
	if (cmd->output)
		cmd->output[rc->oc] = NULL;
}

char	*tokenized(char *org_str)
{
	char	*tokenized_str;
	char	*new;

	tokenized_str = ft_strdup(org_str);
	tokenize1(tokenized_str, org_str, 0);
	tokenize2(tokenized_str, org_str, 0);
	new = ft_strdup(org_str);
	free(tokenized_str);
	return (new);
}

int	start_parse(char *org_str, t_shell *cmd)
{
	char	*newstr;

	if (quote_check(org_str) == -1)
	{
		g_global_exit = 130;
		return (-1);
	}
	org_str = tokenized(org_str);
	newstr = set_dolar(org_str, cmd, 0);
	free(org_str);
	if (newstr == NULL)
		return (-1);
	if (pipe_ba(newstr, 0) == -1)
		return (free(newstr), -1);
	if (struct_filler(cmd, newstr, 0) == 0)
		return (free(newstr), 0);
	else
	{
		free(newstr);
		if (cmd->cmd)
			free(cmd->cmd);
		return (-1);
	}
}
