/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:02:42 by nkarabul          #+#    #+#             */
/*   Updated: 2023/12/07 22:17:09 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*str1;
	const char	*str2;
	size_t		i;

	str2 = src;
	str1 = dst;
	i = 0;
	if (dst == src || len == 0)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (i < len)
		{
			str1[len - 1 - i] = str2[len - 1 - i];
			i++;
		}
	}
	return (dst);
}
