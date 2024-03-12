/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:12:59 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/12 23:00:07 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
# define TILE_SIZE_2D 16


uint32_t	color_minimap(t_map *map, t_player *player, int m_x, int m_y)
{
	(void) player;
	if (m_y >= map->map_height || m_y < 0 || m_x >= map->map_width || m_x < 0)
		return (0x000000FF);
	if (map->grid[m_y] && m_x < (int)strlen(map->grid[m_y]))
		if (map->grid[m_y][m_x] == '1')
			return (0xFFFFFFFF);
	int p_x = (player->p_x - (TILE_SIZE / 2)) / TILE_SIZE;
	int p_y = (player->p_y - (TILE_SIZE / 2)) / TILE_SIZE;
	if (m_x == p_x && m_y == p_y)
	{
		printf("x: %d\n", p_x);
		printf("y: %d\n", p_y);
		return (0xFFFF00FF);
	}
	return (0x0000FFFF);

}

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
void	draw_2d_map_grid(t_game *game, double tile_size_2d)
{
	(void) tile_size_2d;
	t_player *player = game->player;
	t_draw_info	draw_info;
	int			start_x = (game->player->p_x - (TILE_SIZE / 2)) / TILE_SIZE;
	int			start_y = (game->player->p_y - (TILE_SIZE / 2)) / TILE_SIZE;
	int			offset_x = 5 - start_x;
	int			offset_y = 5 - start_y;
	int			m_x;
	int			m_y;
	for (int y = -5; y <= 5; y++)
	{
		for (int x = -5; x <= 5; x++)
		{
			m_x = start_x + x;
			m_y = start_y + y;
			uint32_t color = color_minimap(game->map, game->player, m_x, m_y);

			if (x == 0 && y == 0)
				color = 0x00FF00FF;
			draw_info.y1 = (start_y + y + offset_y) * TILE_SIZE_2D + TILE_SIZE_2D / 2;
			draw_info.x1 = (start_x + x + offset_x) * TILE_SIZE_2D + TILE_SIZE_2D / 2;
			draw_info.color = color;
			draw_info.size = TILE_SIZE_2D;
			draw_square(game->image, &draw_info);
		}
	}
	draw_info.color = 0xFFFF00FF;
	draw_info.color = color_minimap(game->map, game->player, start_x, start_y);
	draw_info.y1 = (start_y + offset_y) * TILE_SIZE_2D + TILE_SIZE_2D / 2;
	draw_info.x1 = (start_x + offset_x) * TILE_SIZE_2D + TILE_SIZE_2D / 2;
	draw_info.size = PLAYER_SIZE;
	draw_square(game->image, &draw_info);
	draw_info.y2 = draw_info.y1 + PLAYER_SIZE * 2 * sin(player->p_a);
	draw_info.x2 = draw_info.x1 + PLAYER_SIZE * 2 * cos(player->p_a);
	draw_line(game->image, &draw_info);
//	int			i;
//	int			j;
//	t_draw_info	draw_info;
//
//	i = 0;
//	draw_info.y1 = tile_size_2d / 2;
//	while (game->map->grid[i])
//	{
//		draw_info.x1 = tile_size_2d / 2;
//		j = 0;
//		while (game->map->grid[i][j])
//		{
//			draw_info.size = tile_size_2d;
//			if (game->map->grid[i][j] == '1')
//				draw_info.color = 0xFFFFFFFF;
//			else if (game->map->grid[i][j] == '0')
//				draw_info.color = 0xB99470FF;
//			draw_square(game->image, &draw_info);
//			draw_info.x1 += tile_size_2d;
//			j++;
//		}
//		draw_info.y1 += tile_size_2d;
//		i++;
//	}
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
void	draw_2d_rays(mlx_image_t *image, t_player *player, t_ray *ray,
	double mini_map_scale)
{
	t_draw_info	draw_info;

	draw_info.y1 = player->p_y / mini_map_scale;
	draw_info.x1 = player->p_x / mini_map_scale;
	draw_info.y2 = ray->r_y / mini_map_scale;
	draw_info.x2 = ray->r_x / mini_map_scale;
	draw_info.color = ray->color;
	draw_line(image, &draw_info);
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
void	draw_2d_player(mlx_image_t *image, t_player *player,
	double mini_map_scale)
{
	t_draw_info	draw_info;

	draw_info.color = 0xFFFF00FF;
	draw_info.y1 = player->p_y / mini_map_scale;
	draw_info.x1 = player->p_x / mini_map_scale;
	draw_info.size = PLAYER_SIZE / mini_map_scale;
	draw_square(image, &draw_info);
	draw_info.y1 = player->p_y / mini_map_scale;
	draw_info.x1 = player->p_x / mini_map_scale;
	draw_info.y2 = (player->p_y + 50 * sin(player->p_a)) / mini_map_scale;
	draw_info.x2 = (player->p_x + 50 * cos(player->p_a)) / mini_map_scale;
	draw_line(image, &draw_info);
}
