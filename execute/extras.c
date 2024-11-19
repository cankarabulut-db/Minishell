/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:08:20 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:08:20 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

char	*get_cmd_from_absolute_path(t_shell *shell)
{
	if (ft_strchr(shell->cmd, '/'))
	{
		if (is_directory(shell->cmd))
			if (runcommanderror(&shell->cmd, 2))
				return (NULL);
		if (!is_file(shell->cmd))
			if (runcommanderror(&shell->cmd, 0))
				return (NULL);
		if (access(shell->cmd, X_OK))
			if (runcommanderror(&shell->cmd, 1))
				return (NULL);
		if (access(shell->cmd, X_OK) == 0)
			return (ft_strdup(shell->cmd));
	}
	return (NULL);
}

char	*find_executable_in_path(t_shell *shell, int path_index)
{
	char	**path_dirs;
	char	*joined_path;
	char	*full_cmd_path;
	int		index;

	index = 0;
	path_dirs = split_path_directories(shell, path_index);
	full_cmd_path = NULL;
	while (path_dirs && path_dirs[index])
	{
		joined_path = ft_strjoin(path_dirs[index], "/");
		full_cmd_path = ft_strjoin(joined_path, shell->cmd);
		free(joined_path);
		if (access(full_cmd_path, X_OK) == 0)
			break ;
		free(full_cmd_path);
		full_cmd_path = NULL;
		index++;
	}
	free_path_directories(path_dirs);
	return (full_cmd_path);
}

void	mini_print(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
}

char	*find_executable_path(t_shell *shell, int path_index)
{
	char	*cmd_path;

	cmd_path = get_cmd_from_absolute_path(shell);
	if (cmd_path)
		return (cmd_path);
	if (ft_strchr(shell->cmd, '/') && !cmd_path)
		return (NULL);
	if (path_index == -1)
	{
		if (!cmd_path && !access(shell->cmd, X_OK))
			return (shell->cmd);
		mini_print(shell->cmd);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_global_exit = 127;
		return (NULL);
	}
	else
		cmd_path = find_executable_in_path(shell, path_index);
	if (!cmd_path)
	{
		mini_print(shell->cmd);
		ft_putstr_fd(": command not found\n", 2);
		g_global_exit = 127;
	}
	return (cmd_path);
}
