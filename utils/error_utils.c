/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:12:46 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/09 20:16:23 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *str1, int i)
{
	if (i == PIPE)
		printf("kurdishell : syntax error near unexpected token `|`\n");
	else if (i == 1)
		printf("kurdishell : syntax error near unexpected token `newline'\n");
	else if (i == INPUT)
		printf("kurdishell : syntax error near unexpected token `<'\n");
	else if (i == OUTPUT)
		printf("kurdishell : syntax error near unexpected token `>'\n");
	else if (i == HEREDOC)
		printf("kurdishell : syntax error near unexpected token `<<'\n");
	else if (i == APPEND)
		printf("kurdishell : syntax error near unexpected token `>>'\n");
	else if(i == 14)
		printf("Malloc!\n");
	free(str1);
}
