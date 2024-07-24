/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:44:17 by nkarabul          #+#    #+#             */
/*   Updated: 2023/12/06 15:45:36 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	x;
	char	*str;

	x = 0;
	str = (char *)b;
	while (x < len)
	{
		str[x] = c;
		x++;
	}
	return (b);
}
