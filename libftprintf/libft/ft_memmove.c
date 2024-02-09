/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:42:43 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/20 13:05:05 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
	{
		return (0);
	}
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((char *) dest)[i] = ((char *) src)[i];
			i++;
		}
	}
	else
	{
		i = n - 1;
		while (i < n)
		{
			((char *) dest)[i] = ((char *) src)[i];
			i--;
		}
	}
	return (dest);
}
