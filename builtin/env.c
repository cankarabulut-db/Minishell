/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmeetkaar <ahmeetkaar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:39:56 by erkoc             #+#    #+#             */
/*   Updated: 2024/11/07 18:45:44 by ahmeetkaar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strarrlen(char **arr)
{
	size_t	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_strequ(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*s1)
	{
		if (*s1 - *s2)
			return (0);
		s2++;
		s1++;
	}
	return (1);
}

int	find_env_index(char **env, char *var)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (i < ft_strarrlen(env))
	{
		temp = ft_substr(env[i], 0, (int)(ft_strchr(env[i], '=') - env[i]));
		if (temp == NULL)
			return (-1);
		if (ft_strequ(temp, var))
			return (free(temp), i);
		free(temp);
		i++;
	}
	return (-1);
}

void	set_env(char **env, char *var, char *value)
{
	char	*temp;
	int		i;
	size_t	env_size;

	i = ft_strarrlen(env);
	env_size = ft_strlen(var) + ft_strlen(value) + 2;
	temp = get_env(env, var);
	if (ft_strequ(temp, ""))
	{
		free(temp);
		return ;
	}
	else
	{
		i = find_env_index(env, var);
		free(temp);
	}
	free(env[i]);
	env[i] = ft_calloc(env_size, sizeof(char));
	ft_strlcat(env[i], var, env_size);
	ft_strlcat(env[i], "=", env_size);
	ft_strlcat(env[i], value, env_size);
	if (temp == NULL)
		env[i + 1] = NULL;
}

void	ft_env(char **env, int status)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (status == 1)
			ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
}
