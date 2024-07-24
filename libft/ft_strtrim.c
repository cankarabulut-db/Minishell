/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:46:36 by nkarabul          #+#    #+#             */
/*   Updated: 2023/12/07 17:56:02 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;
	int		str_len;

	i = 0;
	end = ft_strlen(s1);
	start = 0;
	if (!s1)
		return (NULL);
	while (ft_isset(s1[start], set))
		start++;
	while (end > start && ft_isset(s1[end - 1], set))
		end--;
	str_len = end - start;
	str = malloc(sizeof(char) * str_len + 1);
	if (!str)
		return (NULL);
	while (s1[start] != 0 && str_len-- > 0)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
