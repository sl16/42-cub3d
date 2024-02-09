/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:06:24 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/29 19:40:08 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_to_trim(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*str;

	if (!s1 || !set)
	{
		return (0);
	}
	start = (char *) s1;
	end = start + ft_strlen(s1);
	while (*start != '\0' && ft_to_trim(*start, set) == 1)
	{
		start++;
	}
	while (end > start && ft_to_trim(*(end - 1), set) == 1)
	{
		end--;
	}
	str = ft_substr(start, 0, end - start);
	return (str);
}
