/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:21:12 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/07 19:43:26 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *get_env_val(char *str, t_shell *cmd)
{
	int i;

	i = 0;
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], str, ft_strlen(str)) && cmd->env[i][ft_strlen(str)] == '=')
			return (ft_strchr(cmd->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
char  *get_dollar(char *org_str, int *i, t_shell *cmd)
{
	char *key;
	int temp;
	temp = *i;
	while (org_str[*i] && org_str[*i] != '$' && org_str[*i] != 32)
		(*i)++;
	key = ft_substr(org_str, temp, *i - temp);
	return (get_env_val(key, cmd));
}

size_t dollar_count(char *org_str)
{
	size_t i;
	size_t len;

	len = 0;
	i = 0;
	while (org_str[i])
	{
		if (org_str[i] == '$')
			len++;
		i++;
	}
	return (len);
}

char **check_dolar(char *org_str, t_shell *cmd)
{
	char **val;
	int i;
	size_t dollarlen;
	size_t dlr;
	
	dlr = 0;
	dollarlen = dollar_count(org_str);
	val = malloc(sizeof(char *) * (dollarlen + 1));
	i = 0;
	while (org_str[i])
	{
		if (org_str[i++] == '$')
			val[dlr++] = get_dollar(org_str, &i, cmd);
	}
	if (dlr == 0)
	{
		free(val);
		return (NULL);
	}
	val[dlr] = NULL;
	return (val);
}

char *set_dolar(char *org_str, t_shell *cmd)
{
	char **get;
	size_t i;
	size_t temp;
	size_t c;
	char *new;

	c = 0;
	i = 0;
	temp = 0;
	get = check_dolar(org_str, cmd);
	if (!get)
		return (org_str);
	while (org_str[i] && org_str[i] != '$')
			i++;
	new = ft_substr(org_str, 0, i);
	while (org_str[i])
	{
		if (org_str[i++] == '$')
		{
			while (org_str[i] && org_str[i] != '$'
				&& org_str[i] != 32)
				i++;
			if (get[c] != NULL)
				new = ft_strjoin(new, get[c++]);
			if (get[c] == NULL && ++c)
				new = ft_strjoin(new, "");
		}
		temp = i;
		while (org_str[i] && org_str[i] != '$')
			i++;
		new = ft_strjoin(new, ft_substr(org_str, temp, i - temp));
	}
	return (new);
}
