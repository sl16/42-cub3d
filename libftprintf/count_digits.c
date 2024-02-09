/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:40:41 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:41:03 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_digits(int num)
{
	int	digits;

	if (num < 0)
		num *= -1;
	digits = 0;
	while (num != 0)
	{
		digits++;
		num /= 10;
	}
	return (digits);
}
