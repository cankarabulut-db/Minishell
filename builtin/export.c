/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmeetkaar <ahmeetkaar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:22 by akar              #+#    #+#             */
/*   Updated: 2024/11/10 16:53:50 by ahmeetkaar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int valid_identifier(const char *str)
{
	int i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		if (str[i] == ' ')
			return (0);
		i++;
	}
	if ((str[i] == '=' && str[i + 1] == '\0') || (str[i] == '=' && str[i + 1] != '\0'))
		return (0);
	return (1);
}

char *get_identifier(char *arg, char **equals_check)
{
	char *identifier;

	*equals_check = ft_strchr(arg, '=');
	identifier = ft_substr(arg, 0, *equals_check - arg);
	if (!identifier || !valid_identifier(identifier))
	{
		free(identifier);
		return (NULL);
	}
	return (identifier);
}

int identifier_error(char **arg, char *identifier, int *i)
{
	if (!identifier)
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(arg[*i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_global_exit = 1;
		(*i)++;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void mini_export_hlpr(t_shell *mini, char **arg, int i, char *identifier)
{
	if (!check_env(mini, identifier, arg[i]))
	{
		if (!add_new_env(mini, arg[i], 0))
		{
			free(identifier);
			return;
		}
	}
	free(identifier);
}

void ft_export(t_shell *mini, char **arg, int i, char *identifier)
{
	char *equals_check;

	while (arg[i])
	{
		identifier = get_identifier(arg[i], &equals_check);
		if (identifier_error(arg, identifier, &i))
			continue;
		if (equals_check == NULL)
		{
			free(identifier);
			i++;
			continue;
		}
		if (arg[i] != identifier)
			mini_export_hlpr(mini, arg, i, identifier);
		i++;
	}
}
