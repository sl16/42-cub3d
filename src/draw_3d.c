/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:14:29 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/08 17:41:49 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Converts a color represented in RGBA components into a single
 * 32-bit integer.
 *
 * Example:
 * t_clr color = {255, 127, 0, 255};
 * uint32_t int_color = get_color(&color);
 * -> int_color is now 0xFF7F00FF
 * 
 * @param	color	pointer to a t_clr structure which contains the red, green,
 * 					blue, and alpha components of a color.
 * @return	uint32	color as an uint32
 */
static uint32_t	get_color(t_clr *color)
{
	return ((color->r << 24) | (color->g << 16) | (color->b << 8) | color->a);
}

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

int	get_colour_from_pixel(u_int8_t *pixel)
{
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static int	get_px_height(mlx_texture_t *texture, double wall_height,
	double curr_height, double wall_end)
{
	int		px_height;
	double	tile_increment;
	int		wall_start;

	tile_increment = wall_height / TILE_SIZE;
	wall_start = (wall_end - wall_height) - curr_height;
	while(wall_start < curr_height)
		wall_start += tile_increment;
	px_height = (wall_start % TILE_SIZE) * texture->height;
	return (px_height);
}

static void	draw_3d_column_wall(t_game *game, int x, double start,
	double stop, double wall_height, mlx_texture_t* texture)
{
	u_int8_t	*pixel;
	int			pixel_texture_location;

	pixel_texture_location = get_px_height(texture, wall_height, start, stop);
	pixel_texture_location += x % TILE_SIZE;
	pixel_texture_location *= texture->bytes_per_pixel;
	pixel = &texture->pixels[pixel_texture_location];

	while (start < stop)
	{
		mlx_put_pixel(game->image, x, start, get_colour_from_pixel(pixel));
		// mlx_put_pixel(game->image, x, start, 000000);
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
void	draw_3d_game(t_game *game, int ray_counter, mlx_texture_t* texture)
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
	draw_3d_column_wall(game, ray_counter, wall_start, wall_end, wall_height, texture);
	game->ray->color = get_color(&game->map->clr_ceiling);
	draw_3d_column(game, ray_counter, 0, wall_start);
	game->ray->color = get_color(&game->map->clr_floor);
	draw_3d_column(game, ray_counter, wall_end, HEIGHT);
}
