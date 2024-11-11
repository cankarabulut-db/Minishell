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

	env_len = ft_strlen(shell->env[path_index]);  // ---> burada boş gelio seg yiyo
	trimmed_env = ft_substr(shell->env[path_index], 5, env_len - 5);
	path_directories = ft_split(trimmed_env, ':');
	free(trimmed_env);
	return path_directories;
}

void	free_path_directories(char **path_dirs)
{
	int index = 0;
	while (path_dirs[index])
	{
		free(path_dirs[index]);
		index++;
	}
	free(path_dirs);
}
void error_write(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
}

int	runcommanderror(char **command, int i)
{
	if (i == 0)
	{
		error_write(command[0]);
		ft_putendl_fd(": No such file or directory\n", 2);
		g_global_exit = 127;
		return (1);
	}
	else if (i == 1)
	{
		error_write(command[0]);
		ft_putendl_fd(": Permission denied", 2);
		g_global_exit = 126;
		return (1);
	}
	else if (i == 2)
	{
		error_write(command[0]);
		ft_putendl_fd(": is a directory", 2);
		g_global_exit = 126;
		return (1);
	}
	return (0);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISREG(path_stat.st_mode));
}

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
	return NULL;
}

char	*find_executable_in_path(t_shell *shell, int path_index)
{
	char	**path_dirs;
	char	*joined_path, *full_cmd_path = NULL;
	int		index = 0;

	path_dirs =  split_path_directories(shell, path_index);

	while (path_dirs && path_dirs[index])
	{
		joined_path = ft_strjoin(path_dirs[index], "/");
		full_cmd_path = ft_strjoin(joined_path, shell->cmd);
		free(joined_path);
		if (access(full_cmd_path, X_OK) == 0)
			break;
		free(full_cmd_path);
		full_cmd_path = NULL;
		index++;
	}
	free_path_directories(path_dirs);
	return full_cmd_path;
}

char	*find_executable_path(t_shell *shell, int path_index)
{
	char	*cmd_path = get_cmd_from_absolute_path(shell);
	if (cmd_path)
		return cmd_path;
	if (ft_strchr(shell->cmd, '/') && !cmd_path)
		return (NULL);
	if (path_index == -1)
	{
		if (!cmd_path && !access(shell->cmd, X_OK))
			return (shell->cmd);
		ft_putstr_fd("minishell: ", 2);
		
		ft_putstr_fd(shell->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_global_exit = 127;
		return (NULL);
	}
	else
		cmd_path = find_executable_in_path(shell, path_index);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_global_exit = 127;
	}
	return cmd_path;
}
