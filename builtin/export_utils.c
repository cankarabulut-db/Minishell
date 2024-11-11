/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmeetkaar <ahmeetkaar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:59:41 by erkoc             #+#    #+#             */
/*   Updated: 2024/11/07 18:19:02 by ahmeetkaar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	int	find_existing_env_var(t_shell *mini, const char *identifier)
{
	int		j;
	size_t	len;
	char	*env_var;

	j = 0;
	while (mini->env[j])
	{
		env_var = ft_strchr(mini->env[j], '=');
		if (env_var)
		{
			len = env_var - mini->env[j];
			if (ft_strncmp(identifier, mini->env[j], len) == 0
				&& ft_strlen(identifier) == len)
				return (j);
		}
		j++;
	}
	return (-1);
}

	int	update_env_var(t_shell *mini, int j, const char *arg)
{
	char	*new_env_var;

	free(mini->env[j]);
	new_env_var = ft_strdup(arg);
	if (!new_env_var)
		return (0);
	mini->env[j] = new_env_var;
	return (1);
}

int	check_env(t_shell *mini, const char *identifier, const char *arg)
{
	int	j;

	j = 0;
	j = find_existing_env_var(mini, identifier);
	if (j != -1)
		return (update_env_var(mini, j, arg));
	return (0);
}

int	add_new_env(t_shell *mini, const char *arg, int j)
{
	int		env_count;
	char	**new_env;

	j = 0;
	env_count = 0;
	while (mini->env[env_count])
		env_count++;
	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (0);
	while (j < env_count)
	{
		new_env[j] = mini->env[j];
		j++;
	}
	new_env[env_count] = ft_strdup(arg);
	if (!new_env[env_count])
	{
		free(new_env);
		return (0);
	}
	new_env[env_count + 1] = NULL;
	free(mini->env);
	mini->env = new_env;
	return (1);
}
