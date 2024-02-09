/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_decision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:46:20 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:24:55 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_decision(va_list args, t_format *format)
{
	unsigned int	hex;
	int				hex_len;

	if (format->specifier == 'c')
		return (format_char(format, va_arg(args, int)));
	else if (format->specifier == 's')
		return (format_str(format, va_arg(args, char *)));
	else if (format->specifier == 'p')
		return (format_pointer_hex(va_arg(args, unsigned long int), format));
	else if (format->specifier == 'd' || format->specifier == 'i')
		return (format_dec_int(va_arg(args, int), format));
	else if (format->specifier == 'u')
		return (format_unsigned(va_arg(args, unsigned int), format));
	else if (format->specifier == 'x' || format->specifier == 'X')
	{
		hex = va_arg(args, unsigned int);
		hex_len = find_hex_len(hex, format);
		hex_len += format_hex(hex, format);
		return (hex_len);
	}
	else if (format->specifier == '%')
		return (format_char(format, '%'));
	return (0);
}
