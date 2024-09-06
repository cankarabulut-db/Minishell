/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:38:50 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/05 13:12:06 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exist(char *str,char a,int i)
{
	while(str[i])
	{
		if(str[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int ft_strplen(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}