/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:21:04 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 15:22:57 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
/**
 * @brief	Checks if the specified grid cell in the map is a space
 * that the player can move into.
 * 
 * The player can step into a cell if it is either empty ('0') or a player
 * start position ('P').
 *
 * @param	map		pointer to the map struct
 * @param	grid_y	the y coordinate of the grid cell
 * @param	grid_x	the x coordinate of the grid cell
 * @return	true if the player can step into the cell, false otherwise
 */
static bool	can_step_in(t_map *map, int grid_y, int grid_x)
{
	if (map->grid[grid_y][grid_x] == '0')
		return (true);
	return (false);
}

/**
 * @brief	Performs the movement of the player.
 *
 * This function calculates the new position of the player after a move.
 * It checks if the new position is within the map boundaries and if the new
 * position is not a wall. If the new position is valid, it updates
 * the player's position.
 * 
 * The x and y movements are handle separately to allow for 'sliding along
 * the walls' where the movement in one direction is blocked, but the player can
 * still move in the other direction if it's unblocked.
 *
 * @param	map		pointer to the map struct
 * @param	player	pointer to the player struct
 * @param	move_x	the x component of the move
 */
static void	perform_move(t_map *map, t_player *player)
{
	int	new_p_x;
	int	new_p_y;
	int	grid_x;
	int	grid_y;

	new_p_x = round(player->p_x + player->move_x);
	grid_x = new_p_x / TILE_SIZE;
	grid_y = player->p_y / TILE_SIZE;
	if (grid_x >= 0 && grid_x < map->map_width
		&& grid_y >= 0 && grid_y < map->map_height)
	{
		if (can_step_in(map, grid_y, grid_x))
			player->p_x = new_p_x;
	}
	new_p_y = round(player->p_y + player->move_y);
	grid_y = new_p_y / TILE_SIZE;
	grid_x = player->p_x / TILE_SIZE;
	if (grid_y >= 0 && grid_y < map->map_height
		&& grid_x >= 0 && grid_x < map->map_width)
	{
		if (can_step_in(map, grid_y, grid_x))
			player->p_y = new_p_y;
	}
}

/**
 * @brief	Handles the movement keys.
 *
 * Thisunction checks if the movement keys (W, S, A, D, UP, DOWN) are pressed.
 * If a key is pressed, it calculates the move in the x and y directions based
 * on the player's angle and speed. It then calls the perform_move function
 * to perform the move.
 *
 * @param	mlx		pointer to the mlx struct
 * @param	map		pointer to the map struct
 * @param	player	pointer to the player struct
 */
static void	handle_keys_move(mlx_t *mlx, t_map *map, t_player *player)
{
	player->move_x = 0;
	player->move_y = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		player->move_x = cos(player->p_a) * PLAYER_SPEED;
		player->move_y = sin(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		player->move_x = -cos(player->p_a) * PLAYER_SPEED;
		player->move_y = -sin(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		player->move_x = -sin(player->p_a) * PLAYER_SPEED;
		player->move_y = cos(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		player->move_x = sin(player->p_a) * PLAYER_SPEED;
		player->move_y = -cos(player->p_a) * PLAYER_SPEED;
	}
	perform_move(map, player);
}

/**
 * @brief	Handles the rotation keys.
 *
 * This function checks if the rotation keys (Left, Right) are pressed. If a key
 * is pressed, it updates the player's angle based on the rotation speed.
 * It also ensures that the player's angle stays within the range [0, 2*PI].
 *
 * @param	mlx		pointer to the mlx structure
 * @param	player	pointer to the player structure
 */
static void	handle_keys_rotation(mlx_t *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		player->p_a -= ROTATION_SPEED;
		if (player->p_a < 0)
			player->p_a += 2 * M_PI;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		player->p_a += ROTATION_SPEED;
		if (player->p_a > (2 * M_PI))
			player->p_a -= 2 * M_PI;
	}
}

/**
 * @brief	Handles all key actions.
 *
 * This function is called every time to handle all key actions. It checks if
 * the escape key is pressed, in which case it frees the game structure
 * and exits the program. Otherwise it calls the handle_keys_move and
 * handle_keys_rotation functions to handle the movement and rotation keys.
 *
 * @param	param	pointer to the game struct
 */
void	handle_key_actions(void *param)
{
	t_game		*game;
	t_player	*player;
	t_map		*map;

	game = (t_game *) param;
	player = game->player;
	map = game->map;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_game_full(game);
		exit(0);
	}
	handle_keys_move(game->mlx, map, player);
	handle_keys_rotation(game->mlx, player);
}
