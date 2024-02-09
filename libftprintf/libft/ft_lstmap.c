/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:03:59 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/20 16:49:59 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;

	if (!lst || !f || !del)
	{
		return (NULL);
	}
	new_lst = 0;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (tmp)
		{
			ft_lstadd_back(&new_lst, tmp);
		}
		else
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_lst);
}
