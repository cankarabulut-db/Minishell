/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/08/23 18:48:24 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void start_cmd(char **env)
{
	char *temp;
	char *rcmd;

	(void)env;
	while(1)
	{
		rcmd = readline("mini##> ");
		if(!rcmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(rcmd);
		temp = ft_strtrim(rcmd," \t");
		start_parse(temp);
	}
}

int main(int ac, char *av[],char **env) {
	(void)av;
   	if(ac != 1)
		error_msg("Too much arguments.");
	start_cmd(env);
}