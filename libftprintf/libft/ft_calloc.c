/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:44:36 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/21 16:44:57 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buff;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if ((nmemb * size) < nmemb || (nmemb * size) < size)
	{
		return (0);
	}
	buff = malloc(size * nmemb);
	if (!buff)
	{
		return (0);
	}
	ft_bzero(buff, nmemb * size);
	return (buff);
}
