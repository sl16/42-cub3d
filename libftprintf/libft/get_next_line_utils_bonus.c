/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:01 by aulicna           #+#    #+#             */
/*   Updated: 2023/05/01 17:25:39 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr_custom(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c % 256)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c % 256)
		return ((char *) &s[i]);
	return (NULL);
}

size_t	ft_strlen_custom(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_custom(char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (!s1)
	{
		s1 = (char *) malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	str = (char *) malloc(sizeof(char)
			* (ft_strlen_custom(s1) + ft_strlen_custom(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
