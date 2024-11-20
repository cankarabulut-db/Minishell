/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:09:04 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:09:06 by nkarabul         ###   ########.fr       */
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

int	pipe_ba(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == PIPE)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0' || str[i] == PIPE)
				return (error_msg(PIPE));
		}
		i++;
	}
	i = 0;
	if (str[0] == PIPE)
		return (error_msg(PIPE));
	return (0);
}

int	ft_rdrconfirmator(char redirect)
{
	if (redirect == INPUT)
		return (1);
	else if (redirect == OUTPUT)
		return (1);
	else if (redirect == HEREDOC)
		return (1);
	else if (redirect == APPEND)
		return (1);
	return (0);
}

int	heredoc_append_control(char *str, int i)
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
					return (error_msg(str[i]));
				return (error_msg(1));
			}
			while (str[i] == ' ')
				i++;
			if (str[i] == 0 || ft_rdrconfirmator(str[i]))
			{
				if (ft_rdrconfirmator(str[i]))
					return (error_msg(str[i]));
				return (error_msg(1));
			}
		}
		i++;
	}
	return (0);
}

int	input_output_control(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == INPUT || str[i] == OUTPUT)
		{
			i++;
			if (str[i] == 0 || ft_rdrconfirmator(str[i]))
			{
				if (ft_rdrconfirmator(str[i]))
					return (error_msg(str[i]));
				return (error_msg(1));
			}
			while (str[i] == ' ')
				i++;
			if (str[i] == 0 || ft_rdrconfirmator(str[i]))
			{
				if (ft_rdrconfirmator(str[i]))
					return (error_msg(str[i]));
				return (error_msg(1));
			}
		}
		i++;
	}
	return (0);
}
