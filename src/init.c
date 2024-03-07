/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:19:30 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/06 14:41:18 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	get_player_angle(char start_dir)
{
	if (start_dir == 'E')
		return (0);
	if (start_dir == 'N')
		return ((3 * M_PI) / 2);
	if (start_dir == 'S')
		return (M_PI / 2);
	else
		return (M_PI);
}

void	init_game_struct(t_game *game)
{
	game->player = calloc(1, sizeof(t_player));
	game->ray = calloc(1, sizeof(t_ray));
	game->player->p_x = (game->map->start_x * TILE_SIZE) + (TILE_SIZE / 2);
	game->player->p_y = (game->map->start_y * TILE_SIZE) + (TILE_SIZE / 2);
	game->player->p_a = get_player_angle(game->map->start_dir);
	game->player->fov_rd = (FOV * M_PI) / 180;
}

bool	init_mlx42(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!game->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_full(game);
		return (false);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_full(game);
		return (false);
	}
	return (true);
}

/**
 * Initializes an empty game structure.
 * 
 * @param game The game structure to initialize.
 * @return 0 if successful, otherwise an error code.
 */
int	init_empty_struct(t_game *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		error_print_exit(ERR_MALLOC_MAP, game);
	game->map->fd = 0;
	game->map->parsed_file = NULL;
	game->map->grid = NULL;
	game->map->map_width = 0;
	game->map->map_height = 0;
	game->map->txt_no = NULL;
	game->map->txt_so = NULL;
	game->map->txt_we = NULL;
	game->map->txt_ea = NULL;
	game->map->clr_floor.rgba = 0;
	game->map->clr_ceiling.rgba = 0;
	game->map->start_count = 0;
	game->map->start_x = -1;
	game->map->start_y = -1;
	game->map->start_dir = '\0';
	game->player = NULL;
	game->ray = NULL;
	return (0);
}
