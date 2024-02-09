/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:08:41 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:43:16 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	loop_print(int *format_num, char c)
{
	int	printed;

	printed = 0;
	while (*format_num > 0)
	{
		ft_putchar_fd(c, 1);
		*format_num -= 1;
		printed++;
	}
	return (printed);
}
