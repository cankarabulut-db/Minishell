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
			return (index);
		}
		free(env_var);
		index++;
	}
	return (-1);
}

void	load_env_vars(t_shell *shell)
{
	int			index;
	extern char	**environ;

	index = 0;
	while (environ[index])
		index++;
	shell->env = malloc(sizeof(char *) * (index + 1));
	index = 0;
	while (environ[index])
	{
		shell->env[index] = ft_strdup(environ[index]);
		index++;
	}
	shell->env[index] = NULL;
}

void	func_total(t_shell *shell)
{
	int		env_len;
	char	*trimmed_env;
	char	**path_directories;

	env_len = ft_strplen(shell->env);
	trimmed_env = ft_substr(shell->env[path_index], 5, env_len - 4);
	path_directories = ft_split(trimmed_env, ':');
}

char	*find_executable_path(t_shell *shell, int path_index)
{
	char	*joined_path;
	char	*full_cmd_path;
	int		index;
	func_total();

	index = -1;
	while (path_directories[++index])
	{
		if (shell->cmd && shell->cmd[0] && shell->cmd[0] == '/')
			full_cmd_path = shell->cmd;
		else
		{
			joined_path = ft_strjoin(path_directories[index], "/");
			full_cmd_path = ft_strjoin(joined_path, shell->cmd);
			free(joined_path);
		}
		if (access(full_cmd_path, X_OK) == 0)
			return (full_cmd_path);
		free(full_cmd_path);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}
