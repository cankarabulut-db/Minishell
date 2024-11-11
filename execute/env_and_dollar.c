/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:21:12 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/11 20:16:54 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int dol_border(char a)
{
	if(ft_isalnum(a) || a == '_' || a == '?')
		return (0);
	return (1);
}
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

int	check_if_same(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 // ahmet bunu strcmp ile düzeltirsin 51. satırda kullanıyorum
	&& ft_strncmp(s2, s1, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}

char  *get_dollar(char *org_str, int *i, t_shell *cmd)
{
	char *key;
	int temp;
	temp = *i;
	if (org_str[*i] == '?')
		return (ft_itoa(g_global_exit));
	while (org_str[*i] && !dol_border(org_str[*i])) // bura erör
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
		if(org_str[i] == SINGLEQ)
			{
				i++;
				while(org_str[i] != SINGLEQ && org_str[i])
					i++;
				i++;
			}
		else if (org_str[i++] == '$' && (ft_isalnum(org_str[i]) || org_str[i] == '_' || org_str[i] == '?'))
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

char *set_dolar(char *org_str, t_shell *cmd,size_t i,size_t temp)
{
	char **get;
	size_t c;
	char *new;

	c = 0;
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
			while (org_str[i] && !dol_border(org_str[i]) && org_str[i] != '?')
				i++;
			if (get[c] != NULL)
				new = ft_strjoin(new, get[c++]);
			else if (get[c] == NULL && ++c)
				new = ft_strjoin(new, "");
			if (org_str[i] == '?')
				i++;
		}
		temp = i;
		while (org_str[i] && org_str[i] != '$')
			i++;
		new = ft_strjoin(new, ft_substr(org_str, temp, i - temp));
	}
	if (ft_strlen(new) == 0)
	{
		free(new);
		return (NULL);
	}
	return (new); // DOLARDAN SONRA ALFANUMERİK BİRŞEY VAR İSE DOLAR YAZDIR
}
