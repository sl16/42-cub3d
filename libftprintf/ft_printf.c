/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:52:36 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:51:02 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	printed;
	t_format		*format;

	i = 0;
	printed = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			format = (t_format *) malloc(sizeof(t_format));
			if (!format)
				return (0);
			i += process_flags_specifier((char *) &s[i + 1], format);
			i += 2;
			printed += format_decision(args, format);
			free(format);
		}
		else
			printed += write(1, &s[i++], 1);
	}
	va_end(args);
	return (printed);
}
