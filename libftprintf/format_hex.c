/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:44:40 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:23:33 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_hex_len(unsigned long int num, t_format *format)
{
	int	i;

	if (num == 0)
	{
		return (1);
	}
	i = 0;
	while (num != 0)
	{
		num /= 16;
		i++;
	}
	if (format->hashtag > 0)
		i += 2;
	return (i);
}

void	format_hex_rec(unsigned long int num, t_format *format)
{
	if (num <= 15)
	{
		if (format->specifier == 'x')
			write(1, &"0123456789abcdef"[num], 1);
		else
			write(1, &"0123456789ABCDEF"[num], 1);
	}
	else
	{
		format_hex_rec(num / 16, format);
		format_hex_rec(num % 16, format);
	}
}

static void	format_hex_hashtag(t_format *format)
{
	if (format->specifier == 'x')
		write(1, "0x", 2);
	else
		write(1, "0X", 2);
	format->hashtag = 0;
}

static int	format_hex_prec_min(unsigned long int num, t_format *format)
{
	int	printed;

	printed = 0;
	if (format->prec == 1)
	{
		if (format->zero == 1)
		{
			if (format->prec_val <= find_hex_len(num, format))
				format->mfw -= find_hex_len(num, format);
			else
				format->mfw -= format->prec_val;
			printed += loop_print(&format->mfw, ' ');
		}
		format->prec_val -= find_hex_len(num, format);
		printed += loop_print(&format->prec_val, '0');
	}
	format->mfw -= find_hex_len(num, format);
	printed += loop_print(&format->mfw, ' ');
	format_hex_rec(num, format);
	if (format->min == 1)
	{
		format->min_val -= (find_hex_len(num, format) + printed);
		printed += loop_print(&format->min_val, ' ');
	}
	return (printed);
}

int	format_hex(unsigned long int num, t_format *format)
{
	int	printed;

	printed = 0;
	if (num == 0)
		return (format_hex_zero(format));
	if (format->prec == 1 || format->min == 1)
		return (format_hex_prec_min(num, format));
	format->mfw -= find_hex_len(num, format);
	if (format->zero == 1)
		printed += loop_print(&format->mfw, '0');
	else
		printed += loop_print(&format->mfw, ' ');
	if (format->hashtag > 0)
		format_hex_hashtag(format);
	format_hex_rec(num, format);
	return (printed);
}
