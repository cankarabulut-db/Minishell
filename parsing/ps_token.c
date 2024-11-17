/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:59:13 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/17 17:17:14 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Tırnak kontorlü yapar eğer char * içerisinde açık bir tırnak varsa hata döndürür.
int	quote_check(char *str) 
{
	int		i;
	int		q_count;
	char	c;

	q_count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && q_count % 2 == 0)
		{
			c = str[i];
			q_count += 1;
		}
		else if (str[i] == c)
			q_count++;
		i++;
	}
	if (q_count % 2 != 0)
	{
		return (error_msg("QUOTE ERROR\n",15));
		free(str);
	}
	return (0);
}

// Bu fonksiyon bir char * içerisinde bulunan tek ve çift tırnakları kaldırır ve tırnaklar olmadan bir dize döner
char	*quote_remover(char *str, int i, int j)
{
	char	*removed;
	int		strsize;

	strsize = ft_strlen(str);
	removed = malloc(sizeof(char) * strsize + 1);
	if(!removed)
	{
		free(str);
		return (NULL);
	}
	while (str[i])
	{
		while (str[i] == DOUBLEQ || str[i] == SINGLEQ)
			i++;
		if (!str[i])
			break;
		removed[j] = str[i];
		j++;
		i++;
	}
	removed[j] = '\0';
	free(str);
	return (removed);
}

// Çift veya tek tırnak bulunursa bunların yerine özel sabitler kullanarak dizeyi günceller
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

// output,input, append, heredoc veya pipe bulunursa bunların yerine özel sabitler kullanarak dizeyi günceller
void	tokenize2(char *str, char *org_str, int i) // str free
{
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			org_str[i] = APPEND;
			org_str[i + 1] = APPEND;
			i += 2;
			continue;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			org_str[i] = HEREDOC;
			org_str[i + 1] = HEREDOC;
			i += 2;
			continue;
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
