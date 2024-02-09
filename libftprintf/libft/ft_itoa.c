/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:02:44 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/21 17:04:22 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_n_len(int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	len;

	len = ft_n_len(n);
	s = (char *) malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	s[len] = '\0';
	if (n == 0)
		s[0] = '0';
	else if (n < 0)
		s[0] = '-';
	len -= 1;
	while (n != 0)
	{
		if (n > 0)
			s[len] = n % 10 + '0';
		else
			s[len] = (n % 10) * (-1) + '0';
		len--;
		n /= 10;
	}
	return (s);
}
