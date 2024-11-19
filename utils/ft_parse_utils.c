/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:09:50 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:09:52 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	empty_maker(char *str, char a, int start, int len)
{
	int	i;

	i = 0;
	i = start;
	while (len + i > start && str[start])
		str[start++] = a;
}

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

int	redirect_counter(char *str, int i, int redirectType)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == redirectType && str[i + 1] == redirectType)
		{
			count++;
			i += 2;
		}
		else if (str[i] == redirectType)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	check_redirect(char *pipe_cmd)
{
	int	i;

	i = -1;
	while (pipe_cmd[++i])
		if (pipe_cmd[i] == HEREDOC || pipe_cmd[i] == OUTPUT || \
		pipe_cmd[i] == INPUT || pipe_cmd[i] == APPEND)
			return (1);
	return (0);
}

int	is_quote(char a)
{
	if (a == DOUBLEQ)
		return (1);
	if (a == SINGLEQ)
		return (1);
	return (0);
}
