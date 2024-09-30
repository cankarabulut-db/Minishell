/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/30 20:30:40 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void struct_initializer(t_shell *cmd)
{
	cmd->append = NULL;
	cmd->args = NULL;
	cmd->cmd = NULL;
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

void	take_env(t_shell *cmd)
{
	int	i;
	extern char **environ;

	i = 0;
	while(environ[i])
		i++;
	cmd->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		cmd->env[i] = ft_strdup(environ[i]);
		i++;
	}
	cmd->env[i] = NULL;
	
}

char *asdad(t_shell *cmd, int i)
{
	char *trimmed;
	char **str;
	char *jd;
	char *sk;

	int len = ft_strlen(cmd->env[i]);
	trimmed = ft_substr(cmd->env[i], 5, len - 4);
	str = ft_split(cmd->env[i], ':');
	i = 0;
	while (str[i])
	{
		jd = ft_strjoin(str[i], "/");
		sk = ft_strjoin(jd, cmd->cmd);
		free(jd);
		if (access(sk, X_OK) == 0)
		{
			return (sk);
		}
		free (sk);
		i++;
	}
	return (NULL);
}

int	ft_strarrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	join_cmd_arg(t_shell *mini)
{
	int arg_c;
	int	i;

	i = 1;
	arg_c = ft_strarrlen(mini->args);
	mini->execve_args = malloc(sizeof(char *) * (arg_c + 2));
	mini->execve_args[0] = ft_strdup(mini->cmd);
	while(mini->args[i - 1])
	{
		mini->execve_args[i] = ft_strdup(mini->args[i - 1]);
		i++;
	}
	mini->execve_args[i] = NULL;
}

void start_cmd(char **env)
{
	t_shell *cmd;
	char *temp;
	char *rcmd;
	cmd = malloc(sizeof(t_shell));
	take_env(cmd);
	(void)env;
	while(1)
	{
		struct_initializer(cmd);
		rcmd = readline("minishell>");
		if(!rcmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(rcmd);
		tab_to_space(rcmd, -1);
		temp = ft_strtrim(rcmd," ");
		start_parse(temp,cmd);
		join_cmd_arg(cmd);
		int z = file_path(cmd);
		char *erkoc = asdad(cmd, z);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			execve(erkoc, cmd->execve_args, cmd->env);
			exit(0);
		}
		waitpid(cmd->pid, 0, 0);
		free(temp);
	}
}

int main(int ac, char *av[],char **env) {
	(void)av;
   	if(ac != 1)
		error_msg("Too much arguments.",99);
	start_cmd(env);
}