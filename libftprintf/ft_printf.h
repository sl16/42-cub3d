/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:01:23 by aulicna           #+#    #+#             */
/*   Updated: 2023/02/20 17:52:53 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>

// Structure holding information about the flags for a particular specifier
typedef struct s_format
{
	int		hashtag;
	int		space;
	int		plus;	
	int		mfw;	
	int		prec;
	int		prec_val;
	int		min;
	int		min_val;
	int		zero;
	char	specifier;
}	t_format;

// ***Formating functions***
// Char
int					format_char(t_format *format, char c);

// Str
int					format_str(t_format *format, char *str);

// Dec - 1st file
int					format_dec_int(int num, t_format *format);
// Dec - 2nd file
int					format_dec_int_minimal_int(t_format *format);
int					format_dec_int_prec_min_negative(int num, t_format *format);
int					format_dec_int_prec_min_positive(int num, t_format *format);

// Unsigned - 1st file
int					format_unsigned(unsigned int num, t_format *format);
unsigned int		unsigned_ft_n_len(unsigned int n);
void				ft_putunsigned_fd(unsigned int n, int fd);
// Unsigned - 2nd file
int					format_unsigned_p_m(unsigned int num, t_format *format);
int					format_unsigned_prec_min_zero(t_format *format);

// Hex - 1st file
int					format_hex(unsigned long int num, t_format *format);
int					find_hex_len(unsigned long int num, t_format *format);
void				format_hex_rec(unsigned long int num, t_format *format);
// Hex - 2nd file
int					format_hex_zero(t_format *format);

// Pointer 
int					format_pointer_hex(unsigned long int add, t_format *format);

// Format decision
int					format_decision(va_list args, t_format *format);

// Functions processing the flags
int					process_flags_specifier(char *s, t_format *format);

// The one and only ft_printf
int					ft_printf(const char *s, ...);

// Complete bonuses functions
int					count_digits(int num);
int					loop_print(int *format_num, char c);

#endif
