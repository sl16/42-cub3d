/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_dec_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:42:49 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 16:39:34 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_dec_int_prec_min_helper(t_format *format)
{
	int	printed;

	printed = 0;
	if (format->prec_val == 0)
		printed += loop_print(&format->mfw, ' ');
	else if (format->zero == 1)
	{
		format->mfw -= 1;
		printed += loop_print(&format->mfw, ' ');
	}
	printed += loop_print(&format->prec_val, '0');
	if (format->min == 1)
	{
		format->min_val -= printed;
		printed += loop_print(&format->min_val, ' ');
	}
	return (printed);
}

static int	format_dec_int_prec_min(int num, t_format *format)
{
	int	printed;

	printed = 0;
	if (num > 0)
		return (format_dec_int_prec_min_positive(num, format));
	else if (num < 0)
		return (format_dec_int_prec_min_negative(num, format));
	else if (format->prec == 0 && format->min == 1 && num == 0)
	{
		ft_putchar_fd('0', 1);
		format->min_val -= 1;
		printed += loop_print(&format->min_val, ' ');
		return (printed + 1);
	}
	else if (format->prec == 1 || format->min == 1)
		return (format_dec_int_prec_min_helper(format));
	return (0);
}

static int	format_dec_int_zero(int num, char *num_str, t_format *format)
{
	int	i;

	if (num < 0)
	{
		ft_putchar_fd(num_str[0], 1);
		i = loop_print(&format->mfw, '0');
		ft_putstr_fd(&num_str[1], 1);
	}
	else
	{
		i = loop_print(&format->mfw, '0');
		ft_putstr_fd(num_str, 1);
	}
	return (i);
}

static void	format_dec_int_plus_space(int *num_len, t_format *format)
{
	if (format->plus > 0)
		ft_putchar_fd('+', 1);
	else if (format->space > 0)
		ft_putchar_fd(' ', 1);
	*num_len += 1;
}

int	format_dec_int(int num, t_format *format)
{
	int		num_len;
	char	*num_str;
	int		i;

	if (num == -2147483648)
		return (format_dec_int_minimal_int(format));
	if (format->prec == 1 || format->min == 1)
		return (format_dec_int_prec_min(num, format));
	i = 0;
	num_str = ft_itoa(num);
	num_len = ft_strlen(num_str);
	format->mfw -= num_len;
	if (format->zero == 1)
		i += format_dec_int_zero(num, num_str, format);
	else
	{
		if ((format->plus > 0 || format->space > 0) && num >= 0)
			format_dec_int_plus_space(&num_len, format);
		i += loop_print(&format->mfw, ' ');
		format_str(format, num_str);
	}
	free(num_str);
	return (num_len + i);
}
