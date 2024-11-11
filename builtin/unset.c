/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:36 by akar              #+#    #+#             */
/*   Updated: 2024/11/11 18:53:43 by akar             ###   ########.fr       */
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
