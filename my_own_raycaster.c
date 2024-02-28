/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_own_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:37:55 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/28 11:45:11 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	draw(void *param)
{
	t_game		*game;
	t_player	*player;
	t_draw_info	draw_info;

	game = (t_game *) param;
	player = game->player;
	// Draw background
	draw_info.y1 = 256;
	draw_info.x1 = 256;
	draw_info.size = HEIGHT;
	draw_info.color = 0x000000FF; // black
	draw_square(game->image, draw_info);
	draw_info.x1 = 768;
	draw_square(game->image, draw_info);
	draw_map_grid(game);
	draw_lines_in_map_grid(game);
	draw_rays(game, game->map, game->player, game->ray);
	// Draw player
	draw_info.y1 = player->p_y;
	draw_info.x1 = player->p_x;
	draw_info.size = PLAYER_SIZE;
	draw_info.color = 0xFFFF00FF;
	draw_square(game->image, draw_info);
	// Draw a line to where the player is looking
	draw_info.y1 = player->p_y;
	draw_info.x1 = player->p_x;
	draw_info.y2 = player->p_dy * 5 + player->p_y;
	draw_info.x2 = player->p_dx * 5 + player->p_x;
	draw_info.size = 3;
	draw_info.color = 0xFFFF00FF;
	draw_line_thickness(game->image, draw_info);
}

int	main(void)
{
	t_game	game;

	init_game_struct(&game);
	print_grid(game.map->grid, game.map->map_height);
	init_mlx42(&game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop_hook(game.mlx, handle_key_actions, &game);
	mlx_loop(game.mlx);
	free_game_struct(&game);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
