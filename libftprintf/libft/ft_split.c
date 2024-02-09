/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:08:50 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/29 11:10:34 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_sep(char check, char c)
{
	if (check == c || check == '\0')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static unsigned int	ft_count_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	num_wrds;

	i = 0;
	num_wrds = 0;
	while (s[i] != '\0')
	{
		if (ft_is_sep(s[i + 1], c) == 1 && ft_is_sep(s[i], c) == 0)
		{
			num_wrds++;
		}
		i++;
	}
	return (num_wrds);
}

static void	ft_fill_arr(char *sub_arr, char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (ft_is_sep(s[i], c) == 0)
	{
		sub_arr[i] = s[i];
		i++;
	}
	sub_arr[i] = '\0';
}

static void	ft_alloc_fill_arr(char **arr, char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	wrds;

	i = 0;
	wrds = 0;
	while (s[i] != '\0')
	{
		if (ft_is_sep(s[i], c) == 1)
		{
			i++;
		}
		else
		{
			j = 0;
			while (ft_is_sep(s[i + j], c) == 0)
			{
				j++;
			}
			arr[wrds] = (char *) malloc(sizeof(char) * (j + 1));
			ft_fill_arr(arr[wrds], &s[i], c);
			i += j;
			wrds++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	unsigned int	num_wrds;
	char			**arr;

	if (!s)
	{
		return (0);
	}
	num_wrds = ft_count_words(s, c);
	arr = (char **) malloc(sizeof(char *) * (num_wrds + 1));
	if (!arr)
	{
		return (0);
	}
	ft_alloc_fill_arr(arr, s, c);
	arr[num_wrds] = NULL;
	return (arr);
}
