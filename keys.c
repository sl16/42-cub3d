/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:21:04 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/26 16:21:42 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	handle_key_actions(void *param)
{
	t_game	    *game;
    t_player    *player;
	t_map		*map;
	// Wall colisions
	double		grid_x;
	double		grid_y;

	game = (t_game *) param;
    player = game->player;
	map = game->map;

	// WALL COLLISSIONS
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_game_struct(game);
		exit(0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)) // move up
	{
		grid_x = player->p_x + player->p_dx; 
		grid_y = player->p_y + player->p_dy; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
    		player->p_x += player->p_dx; 
			player->p_y += player->p_dy; 
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)) // move down
	{
		grid_x = player->p_x - player->p_dx; 
		grid_y = player->p_y - player->p_dy; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
  	      player->p_x -= player->p_dx; 
  	      player->p_y -= player->p_dy; 
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) // move right
	{
		grid_x = player->p_x - player->p_dy; 
		grid_y = player->p_y + player->p_dx; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x -= player->p_dy; 
			player->p_y += player->p_dx; 
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) // move left
	{
		grid_x = player->p_x + player->p_dy; 
		grid_y = player->p_y - player->p_dx; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x += player->p_dy; 
			player->p_y -= player->p_dx; 
		}
	}
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
