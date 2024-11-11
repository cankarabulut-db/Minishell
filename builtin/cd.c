/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:56 by akar              #+#    #+#             */
/*   Updated: 2024/11/09 17:35:59 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	throw_error(char **arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
	g_global_exit = 1;
}

void	if_not_null(char **arg, char *pwd, char *temppwd)
{
	if (arg[1][0] == '/')
	{
		if (chdir(arg[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			g_global_exit = 1;
		}
		free(pwd);
	}
	else if (arg[1][0] != '/')
	{
		free(pwd);
		pwd = getcwd(NULL, 0);
		temppwd = ft_strjoin(pwd, "/");
		free(pwd);
		pwd = ft_strjoin(temppwd, arg[1]);
		free(temppwd);
		if (chdir(pwd) == -1)
			throw_error(arg);
		free(pwd);
	}
}

void	if_null(char *home, t_shell *mini, char *pwd)
{
	char	*temphome;

	home = get_env(mini->env, "HOME");
	temphome = home;
	if (ft_strlen(home) != 0)
		home = ft_strchr(home, '=') + 1;
	if (ft_strlen(home) == 0)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_global_exit = 1;
		free(temphome);
		if (pwd)
			free(pwd);
		return ;
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_global_exit = 1;
	}
	if (pwd)
		free(pwd);
	free(temphome);
}

char	*get_env(char **env, char *var)
{
	char	*res;
	int		i;

	i = find_env_index(env, var);
	if (i == -1)
		return (ft_strdup(""));
	res = ft_strdup(env[i]);
	if (res == NULL)
		return (ft_strdup(""));
	return (res);
}

void	ft_cd(char **arg, t_shell *mini)
{
	char	*pwd;
	char	*temppwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	home = NULL;
	temppwd = ft_strjoin(pwd, "/");
	free(pwd);
	if (arg[1])
		pwd = ft_strjoin(temppwd, arg[1]);
	else
		pwd = NULL;
	free(temppwd);
	if (!(arg[1] == NULL))
		if_not_null(arg, pwd, NULL);
	else
		if_null(home, mini, pwd);
}
