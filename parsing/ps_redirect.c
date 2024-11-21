/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:07:30 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/21 16:49:54 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_malloc(t_shell *cmd, char *str, t_rdr *rdrc)
{
	redirect_size(rdrc, str, cmd);
	if (rdrc->ic > 0)
	{
		cmd->input = malloc(sizeof(char *) * (rdrc->ic + 1));
		if (!cmd->input)
			error_msg(14);
	}
	if (rdrc->oc > 0)
	{
		cmd->output = malloc(sizeof(char *) * (rdrc->oc + 1));
		if (!cmd->output)
			error_msg(14);
	}
	if (rdrc->hc > 0)
	{
		cmd->heredoc = malloc(sizeof(char *) * (rdrc->hc + 1));
		if (!cmd->heredoc)
			error_msg(14);
	}
	if (rdrc->ac > 0)
	{
		cmd->append = malloc(sizeof(char *) * (rdrc->ac + 1));
		if (!cmd->append)
			error_msg(14);
	}
}

int	end_of_rdr_2(char *str, int i)
{
	while (str[i])
	{
		if (is_quote(str[i]) && i++)
		{
			while (str[i] && is_quote(str[i]) == 0)
				i++;
			i++;
			continue ;
		}
		else if (str[i] != ' ' && str[i] && i++)
		{
			while (str[i] != ' ' && !is_quote(str[i]) && str[i])
				i++;
			if (str[i] == ' ')
				break ;
		}
		else if (str[i] == ' ')
			break ;
	}
	return (i);
}

int	end_of_rdr(char *str, int i)
{
	if (is_quote(str[i]))
		return (end_of_rdr_2(str, i));
	else
	{
		while (str[i] != ' ' && str[i] && !ft_rdrconfirmator(str[i]))
		{
			if (is_quote(str[i]) == 1 && i++)
			{
				while (!is_quote(str[i]) && str[i])
					i++;
				if (is_quote(str[i]) && i++)
					continue ;
			}
			i++;
		}
	}
	return (i);
}

char	*qrm(char *str)
{
	return (quote_remover(str, 0, 0));
}

void	redirects_filler(t_shell *cmd, char *str, t_rdr *count, int i)
{
	int	start;

	start = i;
	i = end_of_rdr(str, start);
	if (count->ic > count->icwhile && count->type == INPUT)
	{
		cmd->input[count->icwhile++] = qrm(ft_substr(str, start, i - start));
		cmd->status = INPUT;
	}
	else if (count->oc > count->ocwhile && count->type == OUTPUT)
	{
		cmd->output[count->ocwhile++] = qrm(ft_substr(str, start, i - start));
		cmd->status1 = OUTPUT;
	}
	else if (count->ac > count->acwhile && count->type == APPEND)
	{
		cmd->append[count->acwhile++] = qrm(ft_substr(str, start, i - start));
		cmd->status1 = APPEND;
	}
	else if (count->hc > count->hcwhile && count->type == HEREDOC)
	{
		cmd->heredoc[count->hcwhile++] = qrm(ft_substr(str, start, i - start));
		cmd->status = HEREDOC;
	}
	empty_maker(str, ' ', start, i - start);
}
