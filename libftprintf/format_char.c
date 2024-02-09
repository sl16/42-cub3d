/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:32:27 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 10:21:06 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_char(t_format *format, char c)
{
	int	printed;

	printed = 0;
	format->mfw -= 1;
	printed += loop_print(&format->mfw, ' ');
	ft_putchar_fd(c, 1);
	if (format->min == 1)
	{
		format->min_val -= 1;
		printed += loop_print(&format->min_val, ' ');
	}
	return (printed + 1);
}
