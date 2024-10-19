/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/10/12 17:09:52 by akar             ###   ########.fr       */
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

void tab_to_space(char *str, int i)
{
	while (str[++i])
		if (str[i] == '\t')
			str[i] = 32;
}

void join_cmd_arg_part1(t_shell *mini, int *arg_c, int *i)
{
	*arg_c = ft_strplen(mini->args);
	mini->execve_args = malloc(sizeof(char *) * (*arg_c + 2));
	mini->execve_args[0] = ft_strdup(mini->cmd);
	*i = 1;
}

void join_cmd_arg_part2(t_shell *mini, int *i)
{
	while (mini->args[*i - 1])
	{
		mini->execve_args[*i] = ft_strdup(mini->args[*i - 1]);
		(*i)++;
	}
	mini->execve_args[*i] = NULL;
}

void join_cmd_arg(t_shell *mini)
{
	int arg_c;
	int i;

	join_cmd_arg_part1(mini, &arg_c, &i);
	join_cmd_arg_part2(mini, &i);
}

void start_cmd_part1(t_shell **cmd, char **env)
{
	*cmd = malloc(sizeof(t_shell));
	load_env_vars(*cmd, env); 
}

void start_cmd_part2(t_shell *cmd, char **rcmd, char **temp)
{
	(void)cmd;
	*rcmd = readline("minishell>");
	if (!*rcmd)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	add_history(*rcmd);
	tab_to_space(*rcmd, -1);
	*temp = ft_strtrim(*rcmd, " ");
}

void start_cmd_part3(t_shell *cmd)
{
    int path_index = get_path_index(cmd);
    char *find_path = find_executable_path(cmd, path_index);

    cmd->pid = fork();
    if (cmd->pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (cmd->pid == 0) 
    {
		setup_redirections(cmd);
		    process_heredoc(cmd);

        execve(find_path, cmd->execve_args, cmd->env);
        exit(EXIT_FAILURE);
    }
    else 
    {
        waitpid(cmd->pid, NULL, 0); 
    }
}

void start_cmd(char **env)
{
    t_shell *cmd;
    char *temp;
    char *rcmd;

    start_cmd_part1(&cmd, env);  
    while (1)
    {
        struct_initializer(cmd);
        start_cmd_part2(cmd, &rcmd, &temp);
        
        if (!rcmd || strlen(rcmd) == 0) 
        {
            free(rcmd); 
            continue;
        }

        start_parse(temp, cmd); 
        join_cmd_arg(cmd); 
        start_cmd_part3(cmd); 

        free(temp);
        free(rcmd);
    }
}

int main(int ac, char *av[], char **env)
{
	(void)av;
	if (ac != 1)
		error_msg("Too much arguments.", 99);
	start_cmd(env);
}
