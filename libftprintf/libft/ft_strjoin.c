/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:57:17 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/17 18:46:45 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	total_len;

	if (!s1 || !s2)
	{
		return (0);
	}
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc(sizeof(char) * (total_len + 1));
	if (!str)
	{
		return (0);
	}
	ft_strlcpy(str, s1, total_len + 1);
	ft_strlcat(str, s2, total_len + 1);
	return (str);
}
