/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:08:29 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:08:30 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_path_index(t_shell *shell)
{
	int		index;
	char	*env_var;

	index = 0;
	while (shell->env[index])
	{
		env_var = ft_substr(shell->env[index], 0, 4);
		if (ft_strncmp("PATH", env_var, 4) == 0)
		{
			free(env_var);
			return (index);
		}
		free(env_var);
		index++;
	}
	return (-1);
}

void	load_env_vars(t_shell *shell, char **environment)
{
	int		index;

	index = 0;
	while (environment[index])
		index++;
	shell->env = malloc(sizeof(char *) * (index + 1));
	index = 0;
	while (environment[index])
	{
		shell->env[index] = ft_strdup(environment[index]);
		index++;
	}
	shell->env[index] = NULL;
}

char	**split_path_directories(t_shell *shell, int path_index)
{
	int		env_len;
	char	*trimmed_env;
	char	**path_directories;

	env_len = ft_strlen(shell->env[path_index]);
	trimmed_env = ft_substr(shell->env[path_index], 5, env_len - 5);
	path_directories = ft_split(trimmed_env, ':');
	free(trimmed_env);
	return (path_directories);
}

void	free_path_directories(char **path_dirs)
{
	int	index;

	index = 0;
	while (path_dirs[index])
	{
		free(path_dirs[index]);
		index++;
	}
	free(path_dirs);
}

void	error_write(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
}
