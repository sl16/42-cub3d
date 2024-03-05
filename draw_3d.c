/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:14:29 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/05 16:10:28 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"
/**
 * @brief	Draws a single vertical column of pixels for a 3D wall.
 *
 * This function draws a vertical column of pixels from 'start' to 'stop'
 * at the given x-coordinate. The color of the pixels is determined by
 * 'game->ray->color'.
 * 
 * @param	game	pointer to the game struct
 * @param	x		x-coordinate of the column to draw
 * @param	start	y-coordinate to start drawing from
 * @param	stop	y-coordinate to stop drawing at
 *
 */
static void	draw_3d_column(t_game *game, int x, double start,
	double stop)
{
	while (start < stop)
	{
		mlx_put_pixel(game->image, x, start, game->ray->color);
		start++;
	}
}

/**
 * @brief	Draws a 3D representation of the game world for a given ray.
 *
 * This function calculates the height and vertical position of the wall hit
 * by the current ray, and then draws the wall, the ceiling and floor.
 *
 * The wall height is calculated based on the distance to the wall and
 * the player's field of view. The fisheye effect is corrected by multiplying
 * the total distance by the cosine of the difference between the ray angle and
 * the player angle.
 *
 * The vertical position of the wall (the start and end pixels) is calculated
 * based on the wall height. If the wall extends beyond the screen, the start
 * or end pixel is adjusted to fit within the screen.
 *
 * Finally, the wall, ceiling, and floor are drawn using the draw_3d_column
 * function.
 * 
 * @param	game		pointer to the game state
 * @param	ray_counter	index of the current ray being cast
 */
void	draw_3d_game(t_game *game, int ray_counter)
{
	double	wall_height;
	double	wall_end;
	double	wall_start;

	game->ray->angle_diff = normalize_angle(game->ray->r_a - game->player->p_a);
	game->ray->dist_total *= cos(game->ray->angle_diff);
	wall_height = (TILE_SIZE / game->ray->dist_total)
		* ((WIDTH / 2) / tan(game->player->fov_rd / 2));
	wall_start = (HEIGHT / 2) - (wall_height / 2);
	wall_end = (HEIGHT / 2) + (wall_height / 2);
	if (wall_end > HEIGHT)
		wall_end = HEIGHT;
	if (wall_start < 0)
		wall_start = 0;
	draw_3d_column(game, ray_counter, wall_start, wall_end);
	game->ray->color = 0x89CFF3FF;
	draw_3d_column(game, ray_counter, 0, wall_start);
	game->ray->color = 0xB99470FF;
	draw_3d_column(game, ray_counter, wall_end, HEIGHT);
}
