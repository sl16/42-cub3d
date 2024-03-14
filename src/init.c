/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:19:30 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 16:19:03 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Determines the initial viewing angle of the player.
 *
 * This function determines the initial viewing angle of the player based on the 
 * starting direction specified in the game map. The starting direction can be 
 * one of the four cardinal directions: 'N', 'S', 'E', or 'W'.
 *
 * The function returns the angle in radians, with 'E' being 0, 'N' being 3π/2, 
 * 'S' being π/2, and 'W' (or any other value) being π.
 *
 * @param	start_dir	the starting direction of the player
 * @return	double		the initial viewing angle of the player in radians
 */
static double	get_player_angle(char start_dir)
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

/**
 * @brief	Initializes the game structure by allocating memory for the player 
 * and ray structures, and setting the initial state of the player.
 *
 * The player's initial position is calculated based on the starting position
 * specified in the game map, and is scaled up by the size of the tile to fit
 * within the game world. The player's position is also adjusted to be centered
 * in the middle of the tile.
 *
 * The player's initial viewing angle is determined by the `get_player_angle`
 * function, and the field of view is converted from degrees to radians.
 *
 * @param	game		pointer to the game structure to be initialized
 */
void	init_game_struct(t_game *game)
{
	game->player = ft_calloc(1, sizeof(t_player));
	game->ray = ft_calloc(1, sizeof(t_ray));
	game->player->p_x = (game->map->start_x * TILE_SIZE) + (TILE_SIZE / 2);
	game->player->p_y = (game->map->start_y * TILE_SIZE) + (TILE_SIZE / 2);
	game->player->p_a = get_player_angle(game->map->start_dir);
	game->player->fov_rd = (FOV * M_PI) / 180;
}

/**
 * Initializes the resources of the 'credits' floating rectangle animation
 * 
 * @param game The game structure.
 * @return true if the animation is successfully initialized, false otherwise.
 */
static bool	init_animation(t_game *game)
{
	game->animation_txt = mlx_load_png("./textures/logo2.png");
	if (!(game->animation_txt))
	{
		mlx_close_window(game->mlx);
		error_print(mlx_strerror(mlx_errno));
		free_game_full(game);
		return (false);
	}
	game->animation = mlx_texture_to_image(game->mlx, game->animation_txt);
	if (!(game->animation))
	{
		mlx_close_window(game->mlx);
		error_print(mlx_strerror(mlx_errno));
		free_game_full(game);
		return (false);
	}
	return (true);
}

/**
 * @brief	Initializes the MLX library and creates a new window and image.
 *
 * This function initializes the MLX library with the specified width and height 
 * and a title of "cub3d". It then creates a new image with the same dimensions.
 *
 * If the initialization of the MLX library or the creation of the new image
 * fails, the function closes the window and returns false. If the image cannot
 * be drawn to the window, the function also closes the window and returns
 * false.
 *
 * @param	game	pointer to the game structure
 * @return	bool	true if the initialization was successful, false otherwise
 */
bool	init_mlx42(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!game->mlx)
		return (false);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		return (false);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		return (false);
	}
	init_animation(game);
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
	init_empty_textures(game);
	return (0);
}
