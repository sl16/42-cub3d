/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_dec_int_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:29:53 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/20 13:04:45 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	format_dec_int_min_int_min_val(int *printed, t_format *format)
{
	format->min_val -= (*printed - 1);
	*printed += loop_print(&format->min_val, ' ');
}

int	format_dec_int_minimal_int(t_format *format)
{
	int	printed;

	printed = 11;
	format->mfw -= 11;
	if (format->zero == 1 && format->prec == 0)
	{
		ft_putchar_fd('-', 1);
		printed += loop_print(&format->mfw, '0');
	}
	else
	{
		printed += loop_print(&format->mfw, ' ');
		ft_putchar_fd('-', 1);
	}
	if (format->prec == 1)
	{
		format->prec_val -= 10;
		printed += loop_print(&format->prec_val, '0');
	}
	ft_putstr_fd("2147483648", 1);
	if (format->min == 1)
		format_dec_int_min_int_min_val(&printed, format);
	return (printed);
}

static int	format_dec_int_neg_helper(int num, t_format *format)
{
	int	printed;

	printed = 0;
	format->prec_val -= count_digits(num);
	format->mfw -= (format->prec_val + count_digits(num) + 1);
	printed += loop_print(&format->mfw, ' ');
	ft_putchar_fd('-', 1);
	printed += loop_print(&format->prec_val, '0');
	ft_putnbr_fd(num * (-1), 1);
	printed += count_digits(num) + 1;
	return (printed);
}

int	format_dec_int_prec_min_negative(int num, t_format *format)
{
	int	printed;

	if (format->prec == 1)
	{
		if (format->prec_val <= count_digits(num))
		{
			ft_putnbr_fd(num, 1);
			printed = count_digits(num) + 1;
		}
		else
			printed = format_dec_int_neg_helper(num, format);
	}
	else
	{
		ft_putnbr_fd(num, 1);
		printed = count_digits(num) + 1;
	}
	if (format->min == 1)
	{
		format->min_val -= printed;
		printed += loop_print(&format->min_val, ' ');
	}
	return (printed);
}

int	format_dec_int_prec_min_positive(int num, t_format *format)
{
	int	printed;

	printed = 0;
	format->mfw -= count_digits(num);
	if (format->prec_val <= count_digits(num))
	{
		printed += loop_print(&format->mfw, ' ');
		ft_putnbr_fd(num, 1);
		printed += count_digits(num);
	}
	else
	{
		format->prec_val -= (count_digits(num));
		format->mfw -= format->prec_val;
		printed += loop_print(&format->mfw, ' ');
		printed += loop_print(&format->prec_val, '0');
		ft_putnbr_fd(num, 1);
		printed += count_digits(num);
	}
	if (format->min == 1)
	{
		format->min_val -= printed;
		printed += loop_print(&format->min_val, ' ');
	}
	return (printed);
}
