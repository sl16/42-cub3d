/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:43:50 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:53:30 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	unsigned_ft_n_len(unsigned int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*unsigned_ft_itoa(unsigned int n)
{
	char			*s;
	unsigned int	len;

	len = unsigned_ft_n_len(n);
	s = (char *) malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	s[len] = '\0';
	if (n == 0)
		s[0] = '0';
	len -= 1;
	while (n != 0)
	{
		if (n > 0)
			s[len] = n % 10 + '0';
		else
			s[len] = (n % 10) * (-1) + '0';
		len--;
		n /= 10;
	}
	return (s);
}

void	ft_putunsigned_fd(unsigned int n, int fd)
{
	char	c;

	if (n > 9)
	{
		ft_putunsigned_fd(n / 10, fd);
		ft_putunsigned_fd(n % 10, fd);
	}
	else
	{
		c = n + '0';
		write(fd, &c, 1);
	}
}

static void	format_unsigned_plus_space(unsigned int *num_len, t_format *format)
{
	if (format->plus > 0)
		ft_putchar_fd('+', 1);
	else if (format->space > 0)
		ft_putchar_fd(' ', 1);
	*num_len += 1;
}

int	format_unsigned(unsigned int num, t_format *format)
{
	unsigned int	num_len;
	char			*num_str;
	int				i;

	if (format->prec == 1 || format->min == 1)
		return (format_unsigned_p_m(num, format));
	else
	{
		i = 0;
		num_str = unsigned_ft_itoa(num);
		num_len = ft_strlen(num_str);
		format->mfw -= num_len;
		if (format->zero == 1)
			i += loop_print(&format->mfw, '0');
		else
			i += loop_print(&format->mfw, ' ');
		if (format->plus > 0 || format->space > 0)
			format_unsigned_plus_space(&num_len, format);
		format_str(format, num_str);
		free(num_str);
		return (num_len + i);
	}
}
