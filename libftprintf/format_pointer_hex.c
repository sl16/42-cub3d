/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:45:33 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:25:49 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_pointer_hex_nil(t_format *format)
{
	int	printed;

	printed = 0;
	format->mfw -= 5;
	printed += loop_print(&format->mfw, ' ');
	write(1, "(nil)", 5);
	return (5 + printed);
}

static int	format_pointer_hex_add_min(unsigned long int add,
		t_format *format, int add_len)
{
	int	printed;

	printed = 0;
	write(1, "0x", 2);
	format->specifier = 'x';
	format_hex_rec(add, format);
	format->min_val -= add_len;
	printed += loop_print(&format->min_val, ' ');
	return (add_len + printed);
}

int	format_pointer_hex(unsigned long int add, t_format *format)
{
	int	printed;
	int	add_len;

	if (!add)
		return (format_pointer_hex_nil(format));
	add_len = find_hex_len(add, format) + 2;
	if (format->min == 1)
		return (format_pointer_hex_add_min(add, format, add_len));
	printed = 0;
	format->mfw -= add_len;
	printed += loop_print(&format->mfw, ' ');
	write(1, "0x", 2);
	format->specifier = 'x';
	format_hex_rec(add, format);
	return (add_len + printed);
}
