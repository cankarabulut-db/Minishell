#include "../minishell.h"

int	file_path(t_shell *shell){
	int i;
	char	*temp;

	i = 0;
	while (shell->env[i])
	{
		temp = ft_substr(shell->env[i], 0, 4);
		if (ft_strncmp("PATH", temp, 4) == 0)
		{
			return (i);
		}
		free (temp);
		i++;
	}
	return (-1);
}