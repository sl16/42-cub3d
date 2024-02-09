# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 13:02:34 by aulicna           #+#    #+#              #
#    Updated: 2023/12/12 17:16:15 by vbartos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c \
      ft_isdigit.c \
      ft_isalnum.c \
      ft_isascii.c \
      ft_isprint.c \
      ft_strlen.c \
      ft_memset.c \
      ft_bzero.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_strlcpy.c \
      ft_strlcat.c \
      ft_toupper.c \
      ft_tolower.c \
      ft_strchr.c \
      ft_strrchr.c \
      ft_strncmp.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_strnstr.c \
      ft_atoi.c \
      ft_strdup.c \
      ft_calloc.c \
      ft_substr.c \
      ft_strjoin.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c

SRC_BONUS = ft_lstnew.c \
	    ft_lstadd_front.c \
	    ft_lstsize.c \
	    ft_lstlast.c \
	    ft_lstadd_back.c \
	    ft_lstdelone.c \
	    ft_lstclear.c \
	    ft_lstiter.c \
	    ft_lstmap.c

SRC_GNL = get_next_line_bonus.c \
	  get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

OBJ_GNL = $(SRC_GNL:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

.c.o:
	@gcc $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(OBJ_BONUS) $(OBJ_GNL)
	@ar rc $(NAME) $(OBJ) $(OBJ_BONUS) $(OBJ_GNL)

clean:
	@rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_GNL)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
