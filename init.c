/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:19:30 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/26 16:29:34 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

static void	init_player(t_game *game)
{
	game->player = calloc(1, sizeof(t_player));
	game->player->p_a = 0;
	game->player->p_x = 300;
	game->player->p_y = 300;
	game->player->p_dx = cos(game->player->p_a) * 5;
	game->player->p_dy = sin(game->player->p_a) * 5;
}

static void	init_ray(t_game *game)
{
	game->ray = calloc(1, sizeof(t_ray));
	game->ray->r_x = 0;
	game->ray->r_y = 0;
	game->ray->r_a = 0;
	game->ray->y_offset = 0;
	game->ray->x_offset = 0;
}

int	init_game_struct(t_game *game)
{
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
	game->map->p_y = 3;
	game->map->p_x = 14;
	game->map->map_width = 8;
	game->map->map_height = 8;
	init_player(game);
	init_ray(game);
	return (0);
}
