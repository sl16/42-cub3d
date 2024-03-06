/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:21:04 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/06 09:49:16 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Performs the movement of the player.
 *
 * This function calculates the new position of the player after a move.
 * It checks if the new position is within the map boundaries and if the new
 * position is not a wall. If the new position is valid, it updates
 * the player's position.
 *
 * @param	map		pointer to the map struct
 * @param	player	pointer to the player struct
 * @param	move_x	the x component of the move
 * @param	move_y	the y component of the move
 */
static void	perform_move(t_map *map, t_player *player, double move_x,
	double move_y)
{
	int	new_p_x;
	int	new_p_y;
	int	grid_x;
	int	grid_y;

	new_p_x = roundf(player->p_x + move_x);
	new_p_y = roundf(player->p_y + move_y);
	grid_x = new_p_x / TILE_SIZE;
	grid_y = new_p_y / TILE_SIZE;
	if (grid_y >= 0 && grid_y < HEIGHT && grid_x >= 0 && grid_x < WIDTH)
	{
		if (map->grid[grid_y][grid_x] == '0'
			|| map->grid[grid_y][grid_x] == 'P')
		{
			player->p_x = new_p_x;
			player->p_y = new_p_y;
		}
	}
}

/**
 * @brief	Handles the movement keys.
 *
 * This function checks if the movement keys (W, S, A, D, UP, DOWN) are pressed.
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
	double	move_x;
	double	move_y;

	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		move_x = cos(player->p_a) * PLAYER_SPEED;
		move_y = sin(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		move_x = -cos(player->p_a) * PLAYER_SPEED;
		move_y = -sin(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		move_x = -sin(player->p_a) * PLAYER_SPEED;
		move_y = cos(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		move_x = sin(player->p_a) * PLAYER_SPEED;
		move_y = -cos(player->p_a) * PLAYER_SPEED;
	}
	perform_move(map, player, move_x, move_y);
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
		free_game_struct(game);
		exit(0);
	}
	handle_keys_move(game->mlx, map, player);
	handle_keys_rotation(game->mlx, player);
}
