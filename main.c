/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/07/24 19:34:44 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int take_size_env(char **env)
{
	int i;

	i = 0;
	if(!env)
		return (i);
	while(env[i])
		i++;
	return (i);
}

void take_enviro(t_shell *cmds, t_env *env, int st, char **environ)
{
	int i;

	i = -1;
	if(st == 0)
	{
		env->env = malloc(sizeof(char *) * take_size_env(environ) + 1);
		if(!env->env)
			error_msg("Malloc!\n");
		while(take_size_env(env->env) > ++i)
			env->env[i] = ft_strdup(environ[i]);
		env->env[i] = NULL;
	}
	else
	{
		cmds->env = malloc(sizeof(char *) * take_size_env(env->env) + 1);
		if(!cmds->env)
			error_msg("Malloc!\n");
		while(take_size_env(env->env) > ++i)
			cmds->env[i] = ft_strdup(env->env[i]);
		cmds->env[i] = NULL;
	}
}
void initialize_structs(t_shell *cmd, t_env *env)
{
	cmd = malloc(sizeof(t_shell));
	cmd->main_env = env;
	take_enviro(cmd,env,1,NULL);
	cmd->status = 0;
	cmd->next = NULL;
}

void start_cmd(char **str)
{
	char *rcmd;
	char *temp;
	t_shell cmd;
	t_env *env;
	
	take_enviro(NULL, env, 0, str);
	while(1)
	{
		initialize_structs(&cmd,env);
		str = readline("mini##> ");
		if(!str)
		{
			free(env);
			printf("minishell: invalid input!\n");
			exit(EXIT_FAILURE);
		}
		add_history(str);
		temp = ft_strtrim(rcmd," \t");
	}
}

int main(int ac, char *av[]) {
	extern char **env;
   	if(ac != 1)
		error_msg("Too much arguments.");
	start_cmd(env);
}