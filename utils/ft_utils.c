/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:09:58 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:10:00 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exist(char *str, char a, int i)
{
	while (str[i])
	{
		if (str[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strplen(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	ft_print_s(char a)
{
	if (a > 32 && a <= 126)
		return (1);
	return (0);
}

void	make_empty(char *str, int i)
{
	while (str[++i])
		str[i] = ' ';
}
