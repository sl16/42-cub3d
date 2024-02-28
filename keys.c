/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:21:04 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/28 11:34:46 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	handle_keys_up_down(t_game *game, t_map *map, t_player *player)
{
	double		grid_x;
	double		grid_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		grid_x = player->p_x + player->p_dx;
		grid_y = player->p_y + player->p_dy;
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x += player->p_dx;
			player->p_y += player->p_dy;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		grid_x = player->p_x - player->p_dx;
		grid_y = player->p_y - player->p_dy;
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x -= player->p_dx;
			player->p_y -= player->p_dy;
		}
	}
}

void	handle_keys_right_left(t_game *game, t_map *map, t_player *player)
{
	double		grid_x;
	double		grid_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		grid_x = player->p_x - player->p_dy;
		grid_y = player->p_y + player->p_dx;
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x -= player->p_dy;
			player->p_y += player->p_dx;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		grid_x = player->p_x + player->p_dy;
		grid_y = player->p_y - player->p_dx;
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x += player->p_dy;
			player->p_y -= player->p_dx;
		}
	}
}

void	handle_keys_rotation(t_game *game, t_player *player)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		player->p_a -= ROTATION_SPEED;
		if (almost_less_than(player->p_a, 0, PRECISION))
			player->p_a += 2 * M_PI;
		player->p_dx = cos(player->p_a) * 5;
		player->p_dy = sin(player->p_a) * 5;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		player->p_a += ROTATION_SPEED;
		if (almost_greater_than(player->p_a, (2 * M_PI), PRECISION))
			player->p_a -= 2 * M_PI;
		player->p_dx = cos(player->p_a) * 5;
		player->p_dy = sin(player->p_a) * 5;
	}
}

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
	handle_keys_up_down(game, map, player);
	handle_keys_right_left(game, map, player);
	handle_keys_rotation(game, player);
}
