NAME = cub3d

SRC = my_own_raycaster.c \
		init.c \
		precision.c \
		rays.c \
		draw.c \
		keys.c \
		free.c

OBJ = $(SRC)
OBJ := $(OBJ:%.c=%.o)

HEADER = -I ./inc/

CFLAGS = -Wall -Werror -Wextra -g
MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm

CC = cc

LIBFT_PATH	= libftprintf
LIBFT_NAME	= libftprintf.a
MLX_PATH	= MLX42/build
MLX_NAME	= libmlx42.a

all: libs $(NAME)
	@echo "✅ cub3d executable ready"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< $(HEADER) -o $@

libs:
	@make -s -C $(LIBFT_PATH)
	@mv $(LIBFT_PATH)/$(LIBFT_NAME) .
	@echo "✅ libprintf and MLX42 libraries ready"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) $(MLX_PATH)/$(MLX_NAME) -o $(NAME) $(MLXFLAGS) 

clean:
	@rm -f $(OBJ)
	@make clean -s -C $(LIBFT_PATH)
	@echo "✅ object files deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -f libftprintf.a
	@make fclean -s -C $(LIBFT_PATH)
	@echo "✅ executable files deleted"

re: fclean all

.PHONY: all clean fclean re