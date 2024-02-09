/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:32:12 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/21 17:02:42 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*tmp;

	if (!lst)
	{
		return ;
	}
	if (*lst && del)
	{
		current = *lst;
		while (current)
		{
			tmp = current->next;
			ft_lstdelone(current, del);
			current = tmp;
		}
	}
	*lst = NULL;
}
