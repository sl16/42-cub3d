/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:12:54 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/24 16:37:13 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
	{
		return (0);
	}
	if (start >= ft_strlen(s))
	{
		len = 0;
		start = ft_strlen(s);
	}
	else if (len > ft_strlen(&s[start]))
	{
		len = ft_strlen(&s[start]);
	}
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
	{
		return (0);
	}
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}
