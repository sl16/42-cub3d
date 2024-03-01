/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:19:30 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/01 22:33:32 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

static void	init_player(t_game *game)
{
	game->player = calloc(1, sizeof(t_player));
	game->player->p_a = M_PI;
	game->player->fov_rd = (FOV * M_PI) / 180;
	game->player->p_x = 300;
	game->player->p_y = 300;
	game->player->p_dx = cos(game->player->p_a) * 5;
	game->player->p_dy = sin(game->player->p_a) * 5;
}

static void	init_ray(t_game *game)
{
	game->ray = calloc(1, sizeof(t_ray));
}

int	init_game_struct(t_game *game)
{
	game->degree = 360.0 * M_PI / (360.0 - FOV) / (WIDTH / 4.0);
	game->map = calloc(1, sizeof(t_map));
	game->map->grid = calloc(9, sizeof(char *));
	game->map->grid[0] = ft_strdup("11111111");
	game->map->grid[1] = ft_strdup("10100001");
	game->map->grid[2] = ft_strdup("10100001");
	game->map->grid[3] = ft_strdup("10100001");
	game->map->grid[4] = ft_strdup("10000001");
	game->map->grid[5] = ft_strdup("10000101");
	game->map->grid[6] = ft_strdup("10000001");
	game->map->grid[7] = ft_strdup("11111111");
	game->map->grid[8] = NULL;
	game->map->map_width = 8;
	game->map->map_height = 8;
	game->map->p_y = 3;
	game->map->p_x = 14;

//	game->map->grid = calloc(10, sizeof(char *)); // init the map
//	game->map->grid[0] = ft_strdup("1111111111111111111111111"); //fill the map
//	game->map->grid[1] = ft_strdup("1000000000000000000100001");
//	game->map->grid[2] = ft_strdup("1001000000000P00000000001");
//	game->map->grid[3] = ft_strdup("1001000000000000001000001");
//	game->map->grid[4] = ft_strdup("1001000000000000001000001");
//	game->map->grid[5] = ft_strdup("1001000000100000001000001");
//	game->map->grid[6] = ft_strdup("1001000000000000001000001");
//	game->map->grid[7] = ft_strdup("1001000000001000001000001");
//	game->map->grid[8] = ft_strdup("1111111111111111111111111");
//	game->map->grid[9] = NULL;
//	game->map->map_width = 25;
//	game->map->map_height = 9;
//	game->map->p_y = 3;
//	game->map->p_x = 14;

//	game->map->grid = calloc(25, sizeof(char *));
//	game->map->grid[0] = ft_strdup("111111111111111111111111");
//	game->map->grid[1] = ft_strdup("100000000000000000000001");
//	game->map->grid[2] = ft_strdup("100000000000000000000001");
//	game->map->grid[3] = ft_strdup("100000000000000000000001");
//	game->map->grid[4] = ft_strdup("100000111110000101010001");
//	game->map->grid[5] = ft_strdup("100000100010000000000001");
//	game->map->grid[6] = ft_strdup("100000100010000100010001");
//	game->map->grid[7] = ft_strdup("100000100010000000000001");
//	game->map->grid[8] = ft_strdup("100000110110000101010001");
//	game->map->grid[9] = ft_strdup("100000000000000000000001");
//	game->map->grid[10] = ft_strdup("100000000000000000000001");
//	game->map->grid[11] = ft_strdup("100000000000000000000001");
//	game->map->grid[12] = ft_strdup("100000000000000000000001");
//	game->map->grid[13] = ft_strdup("100000000000000000000001");
//	game->map->grid[14] = ft_strdup("100000000000000000000001");
//	game->map->grid[15] = ft_strdup("100000000000000000000001");
//	game->map->grid[16] = ft_strdup("111111111000000000000001");
//	game->map->grid[17] = ft_strdup("110100001000000000000001");
//	game->map->grid[18] = ft_strdup("110000501000000000000001");
//	game->map->grid[19] = ft_strdup("110100001000000000000001");
//	game->map->grid[20] = ft_strdup("110111111000000000000001");
//	game->map->grid[21] = ft_strdup("110000000000000000000001");
//	game->map->grid[22] = ft_strdup("111111111000000000000001");
//	game->map->grid[23] = ft_strdup("111111111111111111111111");
//	game->map->grid[24] = NULL;
//	game->map->map_width = 24;
//	game->map->map_height = 24;
	init_player(game);
	init_ray(game);
	return (0);
}

int	init_mlx42(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!game->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
