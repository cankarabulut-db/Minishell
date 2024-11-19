/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:05:51 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/17 16:10:36 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	args_quote_passer(char *str, int i)
{
	while ((str[i] >= 32 && str[i] <= 126))
		i++;
	while (str[i])
	{
		if (str[i] == DOUBLEQ || str[i] == SINGLEQ)
		{
			i++;
			while ((str[i] != DOUBLEQ && str[i] != SINGLEQ) && str[i])
			{
				if (str[i] == ' ' && str[i])
					str[i] = CHAR;
				i++;
			}
			continue ;
		}
		i++;
	}
}

void	untokenizer_args(char **str, int i, int j)
{
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == CHAR)
				str[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	*quote_remover1(char *str, int i, int j)
{
	char	*removed;
	int		strsize;

	strsize = ft_strlen(str);
	removed = malloc(sizeof(char) * strsize + 1);
	if (!removed)
		return (NULL);
	while (str[i])
	{
		while (str[i] == DOUBLEQ || str[i] == SINGLEQ)
			i++;
		if (!str[i])
			break ;
		removed[j] = str[i];
		j++;
		i++;
	}
	removed[j] = '\0';
	return (removed);
}

void	args_find_fill(t_shell *cmd, char *str)
{
	char	*temp;

	if (ft_exist(str, DOUBLEQ, 0) || ft_exist(str, SINGLEQ, 0))
	{
		args_quote_passer(str, 0);
		temp = quote_remover1(str, 0, 0);
		cmd->args = ft_split(temp, ' ');
		free(temp);
		untokenizer_args(cmd->args, 0, 0);
	}
	else
		cmd->args = ft_split(str, ' ');
}
