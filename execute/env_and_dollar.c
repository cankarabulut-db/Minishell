/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:07:58 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:08:02 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_val(char *str, t_shell *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], str, ft_strlen(str)) \
			&& cmd->env[i][ft_strlen(str)] == '=')
		{
			free(str);
			return (ft_strdup(ft_strchr(cmd->env[i], '=') + 1));
		}
		i++;
	}
	free(str);
	return (ft_strdup(""));
}

int	check_if_same(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0
		&& ft_strncmp(s2, s1, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}

char	*get_dollar(char *org_str, int *i, t_shell *cmd)
{
	char	*key;
	int		temp;

	temp = *i;
	if (org_str[*i] == '?')
		return (ft_itoa(g_global_exit));
	while (org_str[*i] && !dol_border(org_str[*i]))
		(*i)++;
	key = ft_substr(org_str, temp, *i - temp);
	return (get_env_val(key, cmd));
}

char	**check_dolar(char *org_str, t_shell *cmd)
{
	char	**val;
	int		i;
	size_t	dollarlen;
	size_t	dlr;

	dlr = 0;
	dollarlen = dollar_count(org_str);
	val = malloc(sizeof(char *) * (dollarlen + 1));
	i = 0;
	while (org_str[i])
	{
		if (org_str[i] == SINGLEQ && ++i)
		{
			while (org_str[i] != SINGLEQ && org_str[i])
				i++;
			i++;
		}
		else if (org_str[i++] == '$' && (ft_isalnum(org_str[i]) \
				|| org_str[i] == '_' || org_str[i] == '?'))
			val[dlr++] = get_dollar(org_str, &i, cmd);
	}
	if (dlr == 0)
		return (free(val), NULL);
	val[dlr] = NULL;
	return (val);
}

void	freecpointer(char **str, size_t k)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (i < k)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
