/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:40:32 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:07:53 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_str_null(t_format *format)
{
	int	printed;

	printed = 0;
	format->mfw -= 6;
	printed += loop_print(&format->mfw, ' ');
	ft_putstr_fd("(null)", 1);
	return (6 + printed);
}

static int	format_str_prec_min_print_string(t_format *format, char *str)
{
	int	print_str;
	int	j;

	if (format->prec == 1)
	{
		j = 0;
		while (str[j] && j < format->prec_val)
		{
			ft_putchar_fd(str[j], 1);
			j++;
		}
		format->min_val -= j;
		print_str = j;
	}
	else
	{
		ft_putstr_fd(str, 1);
		format->min_val -= ft_strlen(str);
		print_str = ft_strlen(str);
	}
	return (print_str);
}

static int	format_str_prec_min(t_format *format, char *str)
{
	int	printed;
	int	print_str;

	printed = 0;
	format->mfw -= format->prec_val;
	printed += loop_print(&format->mfw, ' ');
	print_str = format_str_prec_min_print_string(format, str);
	printed += loop_print(&format->min_val, ' ');
	return (printed + print_str);
}

int	format_str(t_format *format, char *str)
{
	int	printed;
	int	str_len;

	if (!str && format->prec && format->prec_val < 6)
		return (0);
	else if (!str && format->prec && format->prec_val >= 6)
		return (format_str_null(format));
	else if (!str)
		return (format_str_null(format));
	printed = 0;
	str_len = ft_strlen(str);
	if (format->prec == 1 || format->min == 1)
		return (format_str_prec_min(format, str));
	format->mfw -= str_len;
	printed += loop_print(&format->mfw, ' ');
	ft_putstr_fd(str, 1);
	return (str_len + printed);
}
