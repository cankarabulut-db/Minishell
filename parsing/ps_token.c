/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:09:32 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/21 16:43:07 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_check(char *str)
{
	int		i;
	int		q_count;
	char	c;

	q_count = 0;
	i = 0;
	c = '\0';
	while (str && str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && q_count % 2 == 0)
		{
			c = str[i];
			q_count += 1;
		}
		else if (c != '\0' && str[i] == c)
			q_count++;
		i++;
	}
	if (q_count % 2 != 0)
		return (error_msg(15));
	return (0);
}

char	*quote_remover(char *str, int i, int j)
{
	char	*removed;
	int		strsize;

	strsize = ft_strlen(str);
	removed = malloc(sizeof(char) * strsize + 1);
	if (!removed)
	{
		free(str);
		return (NULL);
	}
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
	free(str);
	return (removed);
}

void	tokenize1(char *str, char *org_str, int i)
{
	while (str[i])
	{
		if (str[i] == '"')
		{
			str[i] = DOUBLEQ;
			org_str[i] = str[i];
			i++;
			while (str[i] != '"')
				str[i++] = CHAR;
			str[i] = DOUBLEQ;
			org_str[i] = str[i];
		}
		else if (str[i] == '\'')
		{
			str[i] = SINGLEQ;
			org_str[i] = str[i];
			i++;
			while (str[i] != '\'')
				str[i++] = CHAR;
			str[i] = SINGLEQ;
			org_str[i] = str[i];
		}
		i++;
	}
}

void	tokenize2(char *str, char *org_str, int i)
{
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			org_str[i] = APPEND;
			org_str[i + 1] = APPEND;
			i += 2;
			continue ;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			org_str[i] = HEREDOC;
			org_str[i + 1] = HEREDOC;
			i += 2;
			continue ;
		}
		if (str[i] == '>')
			org_str[i] = OUTPUT;
		else if (str[i] == '<')
			org_str[i] = INPUT;
		else if (str[i] == '|')
			org_str[i] = PIPE;
		i++;
	}
}

int	struct_filler(t_shell *cmd, char *str, int i)
{
	t_rdr	list;

	(void)i;
	if (ft_exist(str, PIPE, 0))
	{
		if (split_pipe_and_fill(cmd, str, 0, &list) == -1)
			return (-1);
	}
	else
	{
		if (single_cmd_fill(cmd, str, &list) == -1)
			return (-1);
	}
	return (0);
}
