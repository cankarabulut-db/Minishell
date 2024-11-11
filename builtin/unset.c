/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <username@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:00:00 by username          #+#    #+#             */
/*   Updated: 2023/11/08 12:00:00 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env_var(char *var_name, t_shell  *mini)
{
	int		i;
	int		j;
	size_t	len;

	if (!var_name || !mini->env)
		return ;
	len = ft_strlen(var_name);
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var_name, len) == 0 && mini->env[i][len] == '=')
		{
			free(mini->env[i]);
			j = i;
			while (mini->env[j])
			{
				mini->env[j] = mini->env[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}
