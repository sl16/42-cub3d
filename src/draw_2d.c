/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:55:55 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 15:20:38 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
static void	draw_2d_player(t_game *game, t_player *player)
{
	t_draw_info	draw_info;
	int			start_x;
	int			start_y;
	int			offset_x;
	int			offset_y;

	start_x = (game->player->p_x - (TILE_SIZE / 2)) / TILE_SIZE;
	start_y = (game->player->p_y - (TILE_SIZE / 2)) / TILE_SIZE;
	offset_x = MINIMAP_ZOOM - start_x;
	offset_y = MINIMAP_ZOOM - start_y;
	draw_info.color = COLOR_PLAYER;
	draw_info.y1 = (start_y + offset_y) * TILE_SIZE_2D + TILE_SIZE_2D;
	draw_info.x1 = (start_x + offset_x) * TILE_SIZE_2D + TILE_SIZE_2D;
	draw_info.size = PLAYER_SIZE;
	draw_square(game->image, &draw_info);
	draw_info.y2 = draw_info.y1 + PLAYER_SIZE * 2 * sin(player->p_a);
	draw_info.x2 = draw_info.x1 + PLAYER_SIZE * 2 * cos(player->p_a);
	draw_line(game->image, &draw_info);
}

/**
 * @brief	Determines the color of a tile on the mini-map.
 *
 * The color is determined based on whether the position is outside the map,
 * inside a wall, or in free space.
 *
 * The function first checks if the given position is outside the map
 * boundaries. If it is, the function returns the color for outside the map.
 * 
 * If the position is within the map boundaries, the function checks if
 * there is a wall at the position. If there is, the function returns the color
 * for a wall. If there is no wall, the function returns the color for free
 * space.
 *
 * @param	map			pointer to the map struct
 * @param	m_x			the x-coordinate on the mini-map
 * @param	m_y			the y-coordinate on the mini-map
 * @return	uint32_t	the color for the given position
 */
static uint32_t	pick_color_minimap(t_map *map, int m_x, int m_y)
{
	if (m_y >= map->map_height || m_y < 0 || m_x >= map->map_width || m_x < 0)
		return (COLOR_OUTSIDE_2D);
	if (map->grid[m_y] && m_x < (int)strlen(map->grid[m_y]))
		if (map->grid[m_y][m_x] == '1')
			return (COLOR_WALL_2D);
	return (COLOR_FREE_SPACE_2D);
}

/**
 * @brief	Draws a 2D mini-map of the game.
 *
 * This function draws a square for each tile in the vicinity of the player's
 * position on the mini-map. The color of each square is determined
 * by the `color_minimap` function.
 *
 * The player's position is centered in the middle of the minimap, with
 * a set number, as defined by MINIMAP_ZOOM, of tiles around.
 *
 * After all the squares have been drawn, the function calls `draw_2d_player`
 * to draw the player on the mini-map.
 *
 * @param	game		pointer to the game struct
 * @param	player		pointer to the player struct
 */
void	draw_2d_minimap(t_game *game, t_player *player)
{
	int			i;
	int			j;
	t_draw_info	draw_info;

	player->mini_p_x = (game->player->p_x - (TILE_SIZE / 2)) / TILE_SIZE;
	player->mini_p_y = (game->player->p_y - (TILE_SIZE / 2)) / TILE_SIZE;
	i = -MINIMAP_ZOOM;
	while (i <= MINIMAP_ZOOM)
	{
		j = -MINIMAP_ZOOM;
		while (j <= MINIMAP_ZOOM)
		{
			draw_info.color = pick_color_minimap(game->map,
					player->mini_p_x + j, player->mini_p_y + i);
			draw_info.y1 = (player->mini_p_y + i + MINIMAP_ZOOM
					- player->mini_p_y) * TILE_SIZE_2D + TILE_SIZE_2D / 2;
			draw_info.x1 = (player->mini_p_x + j + MINIMAP_ZOOM
					- player->mini_p_x) * TILE_SIZE_2D + TILE_SIZE_2D / 2;
			draw_info.size = TILE_SIZE_2D;
			draw_square(game->image, &draw_info);
			j++;
		}
		i++;
	}
	draw_2d_player(game, player);
}
