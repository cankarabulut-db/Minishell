/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:12:46 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/17 18:11:14 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_msg(int i)
{
	if (i == PIPE)
		ft_putstr_fd("minishell : syntax error near unexpected token `|`\n", 2);
	else if (i == 1)
		ft_putstr_fd("minishell : syntax error near unexpected token\
 `newline'\n", 2);
	else if (i == INPUT)
		ft_putstr_fd("minishell : syntax error near unexpected token `<'\n", 2);
	else if (i == OUTPUT)
		ft_putstr_fd("minishell : syntax error near unexpected token `>'\n", 2);
	else if (i == HEREDOC)
		ft_putstr_fd("minishell : syntax error near unexpected token\
 `<<'\n", 2);
	else if (i == APPEND)
		ft_putstr_fd("minishell : syntax error near unexpected token\
 `>>'\n", 2);
	else if (i == 14)
		ft_putstr_fd("Malloc!\n", 2);
	else if (i == 15)
		ft_putstr_fd("Quote Error!\n", 2);
	g_global_exit = 258;
	return (-1);
}
