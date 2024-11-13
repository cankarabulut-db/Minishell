/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:59:11 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/13 19:06:19 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void one_cmd(t_shell *cmd)
{
	if (is_builtin(cmd->execve_args[0]))
	{
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
		{
			exit(1);
			return ;
		}
		execute_builtin(cmd->execve_args, cmd);
		return ;
	}
    int path_index = get_path_index(cmd);
    char *find_path = find_executable_path(cmd, path_index);
	if (!find_path)
		exit(g_global_exit);
    execve(find_path, cmd->execve_args, cmd->env);
	exit(127);
}
void one_cmd_2(t_shell *cmd, int cmdcount)
{
    if (is_builtin(cmd->execve_args[0]) && cmdcount == 1)
	{
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
		{
			g_global_exit = 1;
			return ;
		}
		execute_builtin(cmd->execve_args, cmd);
		return ;
	}
    int path_index = get_path_index(cmd);
    char *find_path;

	find_path = find_executable_path(cmd, path_index); 
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (!find_path)
			exit(g_global_exit);
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
			exit(1);
		if (is_builtin(cmd->execve_args[0]) && cmdcount == 1)
		{
			execute_builtin(cmd->execve_args, cmd);
			exit(0);
		}
        execve(find_path, cmd->execve_args, cmd->env);
		exit(127);
	}
}

void struct_initializer(t_shell *cmd)
{
	cmd->cur_ap = 0;
	cmd->cur_i = 0;
	cmd->cur_o = 0;
	cmd->append = NULL;
	cmd->args = NULL;
	cmd->ifd = -1;
	cmd->ofd = -1;
	cmd->fd_error = 0;
	cmd->status = -1;
	cmd->status1 = -1;
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
    t_shell *temp = mini;
    while (mini)
    {
        join_cmd_arg_part1(mini, &arg_c, &i);
        join_cmd_arg_part2(mini, &i);
        mini = mini->next;
    }
    mini = temp;
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


void  pipe_exec(t_shell *cmd)
{
	int	fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipi error\n");
		exit(127);
	}
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		setup_redirections(cmd);
		if (cmd->fd_error == 1)
			exit(1);
		one_cmd(cmd);
		exit(127);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void wait_childs(t_shell *cmd, int i)
{
	int status;
	t_shell *temp;
	pid_t	j;

	if (i == 1 && is_builtin(cmd->cmd))
		return ;
	temp = cmd;
	while (cmd)
    {
		signal(SIGINT, &handle_sigint);
		j = waitpid(cmd->pid, &status, 0);
		if (j < 0)
			continue ;
		if (WIFEXITED(status))
			g_global_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global_exit = 128 + WTERMSIG(status);
		cmd = cmd->next;
    }
	cmd = temp;
}

int cmd_counter(t_shell *cmd)
{
	t_shell *temp;
	int		i;

	i = 0;
	temp = cmd;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	cmd = temp;
	return (i);
}
void start_cmd_part3(t_shell *cmd, char *str)
{
    (void)str; // kullanılmıyor kaldır buradan
    int fd[2];
	int cmdcount;

	cmdcount = cmd_counter(cmd);
    fd[0] = dup(0);
    fd[1] = dup(1);
    t_shell *temp = cmd;
    while (cmd)
    {
        if (cmd->next)
            pipe_exec(cmd);
		else 
            one_cmd_2(cmd, cmdcount); 
        if (cmd->next)
            cmd->next->env = cmd->env;
        cmd = cmd->next;
    }
    dup2(fd[0], 0);
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
	cmd = temp;
	wait_childs(cmd, cmdcount);
    cmd = temp;
   
}

void start_cmd(char **env)
{
    t_shell *cmd;
    char *temp;
    char *rcmd;

    start_cmd_part1(&cmd, env); 
    while (1) // -------->> "ls -l" çalışmamalı --> echo '$USER' --> "ls > a > b < c > d"  ab olsumalı d olusmamalı--> env | grep Eray çalışmıyor | 
    {
        struct_initializer(cmd);
        start_cmd_part2(cmd, &rcmd, &temp);// "  kk" gibi bir komut verilirse içerideki tüm boşlujları da alıp komutu tamamen alman lazım.
        if (!rcmd || ft_strlen(rcmd) == 0) 
        {
            free(rcmd);
            continue;
        }
        if (start_parse(temp, cmd) != -1) // İSDİRECTORY İS FİLE KONTROLÜ YAP
        {
			join_cmd_arg(cmd);
			start_cmd_part3(cmd, temp); 
			free(temp);
			free(rcmd);
		}
        else
        {
			free(temp);
			free(rcmd);
			continue;
		}
    }
}

int main(int ac, char *av[], char **env)
{
    (void)av;
    if (ac != 1)
    {
		error_msg("Too many arguments.", 99);
		return (1);
	}
    set_signal(MAIN_P);
	
    start_cmd(env);
    
    return 0;
}