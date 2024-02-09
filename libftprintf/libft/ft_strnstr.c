/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:03:58 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/18 19:36:21 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!big && len == 0)
		return (0);
	if (little[j] == '\0')
		return ((char *) big);
	while (big[i] != '\0' && little[j] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len
			&& big[i + j] != '\0')
			j++;
		if (j == ft_strlen(little))
			return (&((char *)big)[i]);
		i++;
	}
	return (0);
}
