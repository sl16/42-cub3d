/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex_zero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:09:48 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:23:19 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_hex_zero_helper(t_format *format)
{
	if (format->prec == 1 && format->min == 1)
	{
		if (format->prec_val <= 0)
			return (loop_print(&format->min_val, ' '));
		else
			return (loop_print(&format->prec_val, '0'));
	}
	else if (format->prec == 1)
		return (loop_print(&format->prec_val, '0'));
	else if (format->zero == 1)
		return (loop_print(&format->mfw, '0'));
	else if (format->min == 1)
	{
		ft_putchar_fd('0', 1);
		format->min_val -= 1;
		return (loop_print(&format->min_val, ' ') + 1);
	}
	ft_putchar_fd('0', 1);
	return (1);
}

int	format_hex_zero(t_format *format)
{
	int	printed;

	printed = 0;
	if (format->prec == 1 && format->zero == 1)
	{
		if (format->prec_val <= 0)
			printed += loop_print(&format->mfw, ' ');
		else
		{
			if (format->prec_val > format->mfw)
				printed += loop_print(&format->prec_val, '0');
			else
				printed += loop_print(&format->mfw, '0');
		}
	}
	else
		printed += format_hex_zero_helper(format);
	return (printed - 1);
}
