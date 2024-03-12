NAME = cub3d

SRC = main.c\
		src/rays.c\
		src/draw_2d.c\
		src/draw_3d.c\
		src/draw_utils.c\
		src/keys.c\
		src/checker_map.c\
		src/checker_arg.c\
		src/init.c\
		src/parser.c\
		src/parser_utils.c\
		src/parser_utils2.c\
		src/free.c\
		src/error.c\
		src/animation.c\
		src/debug.c

OBJ = $(SRC)
OBJ := $(OBJ:%.c=%.o)

HEADER = -I ./inc/

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

LIBFT_PATH	= libftprintf
LIBFT_NAME	= libftprintf.a
MLX_DIR = ./MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm -Ofast
COMPILER_SPEC = -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++

all: libs $(NAME)
	@echo "✅ cub3d executable ready"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< $(HEADER) -o $@

libs:
	@make -s -C $(LIBFT_PATH)
	@mv $(LIBFT_PATH)/$(LIBFT_NAME) .
	@cmake $(MLX_DIR) $(COMPILER_SPEC) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4
	@echo "✅ libprintf and MLX42 libraries ready"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) $(MLX_LIB) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -s -C $(LIBFT_PATH)
	@echo "✅ object files deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -f libftprintf.a
	@make fclean -s -C $(LIBFT_PATH)
	@rm -rf $(MLX_DIR)/build
	@echo "✅ executable files deleted"

re: fclean all

.PHONY: all clean fclean re