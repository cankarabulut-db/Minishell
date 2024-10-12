/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:12:46 by nkarabul          #+#    #+#             */
/*   Updated: 2024/10/12 16:44:44 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *str1, int i)
{
	if (i == PIPE)
		printf("minishell : syntax error near unexpected token `|`\n");
	else if (i == 1)
		printf("minishell : syntax error near unexpected token `newline'\n");
	else if (i == INPUT)
		printf("minishell : syntax error near unexpected token `<'\n");
	else if (i == OUTPUT)
		printf("minishell : syntax error near unexpected token `>'\n");
	else if (i == HEREDOC)
		printf("minishell : syntax error near unexpected token `<<'\n");
	else if (i == APPEND)
		printf("minishell : syntax error near unexpected token `>>'\n");
	else if(i == 14)
		printf("Malloc!\n");
	free(str1);
	exit(1);
}
