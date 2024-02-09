/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:49:21 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:41:07 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_format_struc(t_format *format)
{
	format->hashtag = 0;
	format->space = 0;
	format->plus = 0;
	format->mfw = 0;
	format->prec = 0;
	format->prec_val = 0;
	format->min = 0;
	format->min_val = 0;
	format->zero = 0;
}

static void	process_dot(t_format *format, char *s, int *i)
{
	format->prec = 1;
	format->prec_val = ft_atoi(&s[*i + 1]);
	if (s[*i + 1] == '0')
		*i += 1;
	*i += count_digits(format->prec_val);
}

static void	process_min(t_format *format, char *s, int *i)
{
	format->min = 1;
	while (s[*i] == '-')
		(*i)++;
	format->min_val = ft_atoi(&s[*i]);
	*i += count_digits(format->min_val) - 1;
}

static void	process_mfw(t_format *format, char *s, int *i)
{
	format->mfw = ft_atoi(&s[*i]);
	*i += count_digits(format->mfw) - 1;
}

int	process_flags_specifier(char *s, t_format *format)
{
	int	i;

	init_format_struc(format);
	i = 0;
	while (s[i] == '#' || s[i] == ' ' || s[i] == '+' || s[i] == '.'
		|| ('0' <= s[i] && s[i] <= '9') || s[i] == '-')
	{
		if (s[i] == '#')
			format->hashtag += 1;
		else if (s[i] == ' ')
			format->space += 1;
		else if (s[i] == '+')
			format->plus += 1;
		else if (s[i] == '0')
			format->zero = 1;
		else if ('1' <= s[i] && s[i] <= '9')
			process_mfw(format, s, &i);
		else if (s[i] == '.')
			process_dot(format, s, &i);
		else if (s[i] == '-')
			process_min(format, s, &i);
		i++;
	}
	format->specifier = s[i];
	return (i);
}
