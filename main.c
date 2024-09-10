/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/10 18:47:24 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void struct_initializer(t_shell *cmd)
{
	cmd->append = NULL;
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->env = NULL;
	cmd->flags = NULL;
	cmd->heredoc = NULL;
	cmd->input = NULL;
	cmd->main_env = NULL;
	cmd->next = NULL;
	cmd->output = NULL;
}

void tab_to_space(char *str,int i)
{
	while(str[++i])
		if (str[i] == '\t')
			str[i] = 32;	
}
void start_cmd(char **env)
{
	t_shell *cmd;
	char *temp;
	char *rcmd;

	cmd = malloc(sizeof(t_shell) + 1);
	(void)env;
	while(1)
	{
		struct_initializer(cmd);
		rcmd = readline("kurdishell>");
		if(!rcmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(rcmd);
		tab_to_space(rcmd, -1);
		temp = ft_strtrim(rcmd," \t");
		start_parse(temp,cmd);
	}
}

int main(int ac, char *av[],char **env) {
	(void)av;
   	if(ac != 1)
		error_msg("Too much arguments.",99);
	start_cmd(env);
}