/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:35:55 by nkarabul          #+#    #+#             */
/*   Updated: 2023/12/16 17:58:10 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*numan;

	numan = (t_list *)malloc(sizeof(t_list));
	if (!numan)
		return (NULL);
	numan->content = content;
	numan->next = NULL;
	return (numan);
}
