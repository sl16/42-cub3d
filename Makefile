NAME = cub3d

SRC = main.c\
		src/arg_checker.c\
		src/map_checker.c\
		src/init.c\
		src/parser.c\
		src/free.c\
		src/error.c\
		src/debug.c

OBJ = $(SRC)
OBJ := $(OBJ:%.c=%.o)

HEADER = -I ./inc/

CFLAGS = -Wall -Werror -Wextra -g
MLXFLAGS = -Lminilibx_linux -lmlx -L/usr/lib/X11 -lXext -lX11

CC = cc

LIBFT_PATH	= libftprintf
LIBFT_NAME	= libftprintf.a
MLX_PATH	= minilibx_linux
MLX_NAME	= libmlx.a

all: libs $(NAME)
	@echo "✅ cub3d executable ready"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< $(HEADER) -o $@

libs:
	@make -s -C $(LIBFT_PATH)
	@mv $(LIBFT_PATH)/$(LIBFT_NAME) .
	@echo "✅ libprintf library ready"
	@make -s -C $(MLX_PATH)
	@mv $(MLX_PATH)/$(MLX_NAME) .
	@echo "✅ mlx library ready"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJ)
	@make clean -s -C $(LIBFT_PATH)
	@make clean -s -C $(MLX_PATH)
	@echo "✅ object files deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -f libftprintf.a
	@make fclean -s -C $(LIBFT_PATH)
	@rm -f libmlx.a
	@echo "✅ executable files deleted"

re: fclean all

.PHONY: all clean fclean re