/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unsigned_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:00:57 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:53:11 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_unsigned_prec_min_helper(unsigned int num, t_format *format)
{
	int	printed;

	printed = 0;
	if (format->zero == 1)
	{
		format->mfw -= format->prec_val;
		printed += loop_print(&format->mfw, ' ');
	}
	format->prec_val -= unsigned_ft_n_len(num);
	printed += loop_print(&format->prec_val, '0');
	ft_putunsigned_fd(num, 1);
	printed += unsigned_ft_n_len(num);
	return (printed);
}

int	format_unsigned_p_m(unsigned int num, t_format *format)
{
	int	printed;

	printed = 0;
	if (num == 0)
		return (format_unsigned_prec_min_zero(format));
	else if ((unsigned int) format->prec_val <= unsigned_ft_n_len(num))
	{
		if (format->zero == 1)
		{
			format->mfw -= unsigned_ft_n_len(num);
			printed += loop_print(&format->mfw, ' ');
		}
		ft_putunsigned_fd(num, 1);
		printed += unsigned_ft_n_len(num);
	}
	else
		printed += format_unsigned_prec_min_helper(num, format);
	if (format->min == 1)
	{
		format->min_val -= printed;
		printed += loop_print(&format->min_val, ' ');
	}
	return (printed);
}

static int	format_unsigned_prec_min_zero_helper(t_format *format)
{
	int	printed;

	printed = 0;
	ft_putchar_fd('0', 1);
	format->min_val -= 1;
	printed += loop_print(&format->min_val, ' ');
	return (printed + 1);
}

int	format_unsigned_prec_min_zero(t_format *format)
{
	int	printed;

	printed = 0;
	if (format->prec == 1 && format->min == 1)
	{
		if (format->prec_val == 0 && format->min_val == 0)
			return (0);
		printed += loop_print(&format->prec_val, '0');
		format->min_val -= printed;
		printed += loop_print(&format->min_val, ' ');
	}
	else if (format->prec == 1)
	{
		if (format->zero == 1 && format->prec_val == 0)
			return (loop_print(&format->mfw, ' '));
		if (format->prec_val == 0)
			return (0);
		printed += loop_print(&format->prec_val, '0');
	}
	else if (format->min == 1)
		return (format_unsigned_prec_min_zero_helper(format));
	return (printed);
}
