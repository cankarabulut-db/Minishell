/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:06:27 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/09 20:11:55 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rdr_makezero(t_rdr *count)
{
	count->acwhile = 0;
	count->icwhile = 0;
	count->hcwhile = 0;
	count->ocwhile = 0;
	count->oc = 0;
	count->ic = 0;
	count->ac = 0;
	count->hc = 0;
	count->type = 0;
}

void	pipe_ba(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == PIPE)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0' || str[i] == PIPE)
				error_msg(str, PIPE);
		}
		i++;
	}
	i = 0;
	if(str[0] == PIPE)
		error_msg(str, PIPE);
}
int ft_rdrconfirmator(char redirect)
{
	if(redirect == INPUT)
		return (1);
	else if(redirect == OUTPUT)
		return (1);
	else if(redirect == HEREDOC)
		return (1);
	else if(redirect == APPEND)
		return (1);
	return (0);	
}
void	heredoc_append_control(char *str, int i)
{
	while (str[i])
	{
		if ((str[i] == HEREDOC && str[i + 1] == HEREDOC) || \
			(str[i] == APPEND && str[i + 1] == APPEND))
		{
			i += 2;
			if (str[i] == 0 || ft_rdrconfirmator(str[i]))
			{
				if (ft_rdrconfirmator(str[i]))
					error_msg(str, str[i]);
				error_msg(str, 1);
			}
			while (str[i] == ' ')
				i++;
			if (str[i] == 0 || ft_rdrconfirmator(str[i]))
			{
				if (ft_rdrconfirmator(str[i]))
					error_msg(str, str[i]);
				error_msg(str, 1);
			}
		}
		i++;
	}
}

void	input_output_control(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == INPUT || str[i] == OUTPUT)
		{
			i++;
			if (str[i] == 0 || ft_rdrconfirmator(str[i]))
			{
				if(ft_rdrconfirmator(str[i]))
					error_msg(str, str[i]);
				error_msg(str, 1);
			}
			while (str[i] == ' ')
				i++;
			if (str[i] == 0 || ft_rdrconfirmator(str[i]))
				{
				if(ft_rdrconfirmator(str[i]))
					error_msg(str, str[i]);
				error_msg(str, 1);
				}
		}
		i++;
	}
}

void	redirects_filler(t_shell *cmd, char *str, t_rdr *count, int i)
{
	int	start;

	start = i;
	if ((str[i] == DOUBLEQ || str[i] == SINGLEQ) && i++)
		while ((str[i] != DOUBLEQ && str[i] != SINGLEQ) && str[i])
			i++;
	else
		while (str[i] != ' ' && str[i])
			i++;
	if (count->ic > count->icwhile && count->type == INPUT)
		cmd->input[count->icwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	else if (count->oc > count->ocwhile && count->type == OUTPUT)
		cmd->output[count->ocwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	else if (count->ac > count->acwhile && count->type == APPEND)
		cmd->append[count->acwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	else if (count->hc > count->hcwhile && count->type == HEREDOC)
		cmd->heredoc[count->hcwhile++] = quote_remover(ft_substr(str, start, i - start), 0, 0);
	empty_maker(str, ' ', start, i - start);
}
