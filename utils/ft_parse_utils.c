/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:16:44 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/11 19:08:26 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void empty_maker(char *str,char a,int start,int len)
{
	int i = 0;

	i = start;
	if(str[start] == DOUBLEQ || str[start] == SINGLEQ)
	{
		start++;
		while(len + i > start && str[start] && \
		(str[start] != DOUBLEQ && str[start] != SINGLEQ))
			str[start++] = a;
	}
	else
	{
		while(len + i > start && str[start] && \
		(str[start] != ' ' && str[start] != '\t'))
			str[start++] = a;
	}
	
}

void free_double_ptr(char **str)
{
	int i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void make_empty(char *str,int i)
{
	while(str[++i])
		str[i] = ' ';
}

int redirect_counter(char *str,int i,int redirectType)
{
	int count;

	count = 0;
	while(str[i])
	{
		if(str[i] == redirectType && str[i+1] == redirectType)
		{
			count++;
			i+=2;
		}
		else if(str[i] == redirectType)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}