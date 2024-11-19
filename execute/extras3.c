/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:08:25 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/19 11:08:26 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dol_border(char a)
{
	if (ft_isalnum(a) || a == '_' || a == '?')
		return (0);
	return (1);
}

size_t	dollar_count(char *org_str)
{
	size_t	i;
	size_t	len;

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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

char	*set_dollar_while(char *org_str, char **get, size_t i)
{
	char	*new;
	size_t	temp;
	size_t	c;

	new = ft_substr(org_str, 0, i);
	c = 0;
	while (org_str[i])
	{
		if (org_str[i++] == '$')
		{
			while (org_str[i] && !dol_border(org_str[i]) && org_str[i] != '?')
				i++;
			if (get[c] && get[c][0] != '\0')
				new = ft_strjoin_free(new, get[c++]);
			else if (get[c] && !get[c][0] && ++c)
				new = ft_strjoin_free(new, "");
			if (org_str[i] == '?')
				i++;
		}
		temp = i;
		while (org_str[i] && org_str[i] != '$')
			i++;
		new = ft_strjoin_substr(new, org_str, temp, i - temp);
	}
	return (new);
}

char	*set_dolar(char *org_str, t_shell *cmd, size_t i)
{
	char	**get;
	char	*new;

	get = check_dolar(org_str, cmd);
	if (!get)
		return (ft_strdup(org_str));
	while (org_str[i] && org_str[i] != '$')
		i++;
	new = set_dollar_while(org_str, get, i);
	freecpointer(get, dollar_count(org_str));
	if (ft_strlen(new) == 0)
		return (free(new), NULL);
	return (new);
}
