/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:26:26 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/23 19:35:01 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

// Main functions
char	*get_next_line(int fd);
char	*read_fd(int fd, char *s);
char	*process_current_line(char *s);
char	*save_remainder_of_line(char *s);

// Utility functions
char	*ft_strchr_custom(const char *s, int c);
size_t	ft_strlen_custom(const char *s);
char	*ft_strjoin_custom(char *s1, char *s2);

#endif
