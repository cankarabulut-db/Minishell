/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:49:13 by nkarabul          #+#    #+#             */
/*   Updated: 2023/12/07 18:05:57 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	a;

	a = 0;
	i = 0;
	if (needle[a] == '\0')
		return ((char *)haystack);
	while (haystack[i] && len > i)
	{
		a = 0;
		while (needle[a] && (needle[a] == haystack[i + a]) && len > i + a)
			a++;
		if (needle[a] == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
