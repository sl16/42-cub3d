/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:53:23 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/16 17:27:00 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	if ((!dst) && size == 0)
	{
		return (0);
	}
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0 || size <= dst_len)
	{
		return (src_len + size);
	}
	i = 0;
	while (src[i] != '\0' && i < size - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
