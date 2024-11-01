/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:12:46 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/01 19:55:16 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_msg(char *str1, int i)
{
	if (i == PIPE)
		ft_putstr_fd("minishell : syntax error near unexpected token `|`\n",2);
	else if (i == 1)
		ft_putstr_fd("minishell : syntax error near unexpected token `newline'\n",2);
	else if (i == INPUT)
		ft_putstr_fd("minishell : syntax error near unexpected token `<'\n",2);
	else if (i == OUTPUT)
		ft_putstr_fd("minishell : syntax error near unexpected token `>'\n",2);
	else if (i == HEREDOC)
		ft_putstr_fd("minishell : syntax error near unexpected token `<<'\n",2);
	else if (i == APPEND)
		ft_putstr_fd("minishell : syntax error near unexpected token `>>'\n",2);
	else if(i == 14)
		ft_putstr_fd("Malloc!\n",2);
	else if(i == 15)
		ft_putstr_fd("QUOTE ERROR",2);
	free(str1);
	return (-1);

}
