#include "./inc/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	t_game *game = param;

	for (uint32_t i = 0; i < game->image->width; ++i)
	{
		for (uint32_t y = 0; y < game->image->height; ++y)
		{
			uint32_t color = ft_pixel(
				255 % 0xFF, // R
				255 % 0xFF, // G
				124 % 0xFF, // B
				255  // A
			);
			mlx_put_pixel(game->image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	t_game *game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->image->instances[0].y -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->image->instances[0].y += 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->image->instances[0].x -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->image->instances[0].x += 5;
}

int	init_game_struct(t_game *game)
{
	game->map->map = {
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001    ",
		"11110111111111011101010010001    ",
		"11000000110101011100000010001    ",
		"10000000000000001100000010001    ",
		"10000000000000001101010010001    ",
		"11000001110101011111011110N0111  ",
		"11110111 1110101 101111010001    ",
		"11111111 1111111 111111111111    "
	};
	
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_game	game;

	// Init struct


	// Init mlx and image
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, game.image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
//	mlx_loop_hook(game.mlx, ft_randomize, &game);
//	mlx_loop_hook(game.mlx, ft_hook, &game);

	// Draw in the picture
	int i = 0;
	int height = 300;
	int width = 400;
	while (i < 20)
	{
		mlx_put_pixel(game.image, width + i, height, ft_pixel(255, 255, 0, 255));
		i++;
	}
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);

	return (EXIT_SUCCESS);
}
