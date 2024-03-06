/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:12:59 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/06 09:48:53 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Draws a 2D grid map of the game world.
 *
 * This function iterates over the grid map and draws a square for each grid
 * cell. The color of the square depends on the type of the cell
 * (wall or empty space).
 *
 * The position and size of each square is calculated based on the size of the
 * grid cells and the current indices in the grid iteration.
 *
 * @param	game	pointer to the game struct
 */
void	draw_2d_map_grid(t_game *game)
{
	int			i;
	int			j;
	t_draw_info	draw_info;

	i = 0;
	draw_info.y1 = TILE_SIZE_2D / 2;
	while (game->map->grid[i])
	{
		draw_info.x1 = TILE_SIZE_2D / 2;
		j = 0;
		while (game->map->grid[i][j])
		{
			draw_info.size = TILE_SIZE_2D;
			if (game->map->grid[i][j] == '1')
				draw_info.color = 0xFFFFFFFF;
			else if (game->map->grid[i][j] == '0')
				draw_info.color = 0xB99470FF;
			draw_square(game->image, draw_info);
			draw_info.x1 += TILE_SIZE_2D;
			j++;
		}
		draw_info.y1 += TILE_SIZE_2D;
		i++;
	}
}

/**
 * @brief	Draws a 2D representation of a ray cast from the player.
 *
 * This function draws a line from the player's position to the end point of the
 * ray. The end point of the ray is calculated based on the ray's direction and
 * distance.
 *
 * The position of the player and the end point of the ray are scaled down by
 * the size of the mini map to fit within the 2D map view.
 *
 * @param	image		pointer to the image where the ray is drawn
 * @param	player		pointer to the player struct
 * @param	ray			pointer to the ray being drawn
 */
void	draw_2d_rays(mlx_image_t *image, t_player *player, t_ray *ray)
{
	t_draw_info	draw_info;

	draw_info.y1 = player->p_y / MINI_MAP;
	draw_info.x1 = player->p_x / MINI_MAP;
	draw_info.y2 = ray->r_y / MINI_MAP;
	draw_info.x2 = ray->r_x / MINI_MAP;
	draw_info.color = ray->color;
	draw_line(image, draw_info);
}

/**
 * @brief	Draws a 2D representation of the player.
 *
 * This function draws a square for the player's position and a line for the
 * player's direction of view.
 *
 * The position and size of the player's square and the end point of the view
 * line are calculated based on the player's state and are scaled down by the
 * size of the mini map to fit within the 2D map view.
 *
 * @param	image		pointer to the image where the player is drawn
 * @param	player		pointer to the player struct
 */
void	draw_2d_player(mlx_image_t *image, t_player *player)
{
	t_draw_info	draw_info;

	draw_info.color = 0xFFFF00FF;
	draw_info.y1 = player->p_y / MINI_MAP;
	draw_info.x1 = player->p_x / MINI_MAP;
	draw_info.size = PLAYER_SIZE / MINI_MAP;
	draw_square(image, draw_info);
	draw_info.y1 = player->p_y / MINI_MAP;
	draw_info.x1 = player->p_x / MINI_MAP;
	draw_info.y2 = (player->p_y + 50 * sin(player->p_a)) / MINI_MAP;
	draw_info.x2 = (player->p_x + 50 * cos(player->p_a)) / MINI_MAP;
	draw_line(image, draw_info);
}
