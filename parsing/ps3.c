/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:05:51 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/09 14:05:51 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void args_quote_passer(char *str, int i)
{
	while(str[i] == ' ')
		i++;
	while(str[i])
	{
		if(is_quote(str[i]) && str[i] && i++)
		{
			while(!is_quote(str[i]) && str[i])
				{
					if(str[i] == ' ')
						str[i] = CHAR;
					i++;
				}
		}
		i++;
	}
}

void untokenizer_args(char **str, int i, int j)
{
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if(str[i][j] == CHAR)
				str[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void args_find_fill(t_shell *cmd, char *str)
{
	if(ft_exist(str,DOUBLEQ,0) || ft_exist(str,SINGLEQ,0))
	{
		args_quote_passer(str,0);
		cmd->args = ft_split(str, ' ');
		untokenizer_args(cmd->args, 0, 0);
	}
	else
		cmd->args = ft_split(str,' ');
}
