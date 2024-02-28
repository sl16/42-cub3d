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
	cmake $(MLX_DIR) $(COMPILER_SPEC) -B $(MLX_DIR)/build
	make -C $(MLX_DIR)/build -j4
	@echo "✅ libprintf and MLX42 libraries ready"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) $(MLX_LIB) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -s -C $(LIBFT_PATH)
	@echo "✅ object files deleted"
	rm -rf $(MLX_DIR)/build

fclean: clean
	@rm -f $(NAME)
	@rm -f libftprintf.a
	@make fclean -s -C $(LIBFT_PATH)
	@echo "✅ executable files deleted"

re: fclean all

.PHONY: all clean fclean re