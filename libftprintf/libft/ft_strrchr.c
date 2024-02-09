/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:21:06 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/24 17:00:00 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last_occur;

	i = 0;
	last_occur = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c % 256)
		{
			last_occur = (char *) &s[i];
		}
		i++;
	}
	if (s[i] == c % 256)
	{
		last_occur = (char *) &s[i];
	}
	return (last_occur);
}
