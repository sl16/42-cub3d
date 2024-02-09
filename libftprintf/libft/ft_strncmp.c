/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:22:58 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/21 16:47:11 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
		{
			if (s1[i] != s2[i])
			{
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			}
			i++;
		}
	}
	return (0);
}
