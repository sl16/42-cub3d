/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:01:23 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 16:19:34 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Draws a single vertical column of pixels in 3D representation.
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
static void	draw_column(t_game *game, int x, double start,
	double stop)
{
	while (start < stop)
	{
		mlx_put_pixel(game->image, x, start, game->ray->color);
		start++;
	}
}

/**
 * @brief	Determines the texture to use for a wall based on the angle
 * of the ray that hit the wall.
 * 
 * If the ray hit the wall horizontally, the function checks the normalized
 * angle of the ray:
 * - If the angle is greater than π/2 and less than 3π/2, the function returns
 * the south texture.
 * - Otherwise, it returns the north texture.
 * 
 * If the ray hit the wall vertically, the function checks the normalized angle
 * of the ray:
 * - If the angle is greater than 0 and less than π, the function returns
 * the east texture.
 * - Otherwise, it returns the west texture.
 * 
 * 
 * @param	map				pointer to the map struct
 * @param	ray				pointer to the ray struct
 * @return	mlx_texture_t	pointer to the texture to use for the wall
 */
static	mlx_texture_t	*get_texture(t_map *map, t_ray *ray)
{
	if (ray->angle_orientation == HORIZONTAL)
	{
		if (ray->angle_nor > M_PI / 2 && ray->angle_nor < 3 * (M_PI / 2))
			return (map->mlx_txt_so);
		else
			return (map->mlx_txt_no);
	}
	else if (ray->angle_orientation == VERTICAL)
	{
		if (ray->angle_nor > 0 && ray->angle_nor < M_PI)
			return (map->mlx_txt_ea);
		else
			return (map->mlx_txt_we);
	}
	return (0);
}

/**
 * @brief	Reverses the byte order of a color, from RGBA to ABGR format.
 * 
 * @param	color	original color
 * @return	t_clr	color with reversed byte order
 */
static t_clr	reverse_bytes(t_clr color)
{
	t_clr	reversed_color;

	reversed_color.r = color.a;
	reversed_color.g = color.b;
	reversed_color.b = color.g;
	reversed_color.a = color.r;
	return (reversed_color);
}

/**
 * @brief	Draws a wall column in 3D representation.
 * 
 * The wall column is drawn from `wall_start` to `wall_end` on the y-axis,
 * textured with the texture returned by `get_texture()`.
 * 
 * The x-coordinate of the texture is determined by the exact position where
 * the ray hit the wall. If the ray hit the wall horizontally, the y-coordinate
 * of the hit is used. If the ray hit the wall vertically, the x-coordinate
 * of the hit is used.
 * 
 * The y-coordinate of the texture is determined by the y-coordinate
 * on the screen, adjusted to be relative to the middle of the screen,
 * and offset by half the height of the wall column. This ensures that
 * the texture is centered on the wall column.
 * 
 * The texture's pixel data is accessed as a one-dimensional array, but
 * it represents a two-dimensional image. Therefore, the 2D coordinates 
 * of the texture are converted into a 1D index to access the correct pixel.
 * 
 * The color of the pixel is then reversed to match the color format expected
 * by `mlx_put_pixel()`.
 * 
 * Finally, the column is drawn on the screen at the specified coordinates,
 * moving the y-coordinate by the txt_factor which scales the texture to fit
 * the height of the wall column.
 * 
 * @param	game		pointer to game struct
 * @param	ray			pointer to ray struct
 * @param	x			x-coordinate of the wall column
 * @param	wall		wall struct with wall start, end and height values
 */
static void	draw_wall(t_game *game, t_ray *ray, int x, t_wall wall)
{
	mlx_texture_t	*txt;
	double			txt_x;
	double			txt_y;
	double			txt_factor;
	t_clr			*txt_color_array;

	txt = get_texture(game->map, ray);
	txt_color_array = (t_clr *)txt->pixels;
	txt_factor = floor(txt->height / TILE_SIZE) * TILE_SIZE / wall.wall_height;
	if (ray->angle_orientation == HORIZONTAL)
		txt_x = fmod(ray->r_y, TILE_SIZE) / TILE_SIZE * txt->width;
	else if (ray->angle_orientation == VERTICAL)
		txt_x = fmod(ray->r_x, TILE_SIZE) / TILE_SIZE * txt->width;
	txt_y = ((wall.wall_start - (HEIGHT / 2)
				+ (wall.wall_height / 2)) * txt_factor);
	while (wall.wall_start < wall.wall_end)
	{
		ray->color = reverse_bytes(
				txt_color_array[(int)txt_y * txt->width + (int)txt_x]).rgba;
		mlx_put_pixel(game->image, x, wall.wall_start, ray->color);
		txt_y += txt_factor;
		wall.wall_start++;
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
 * Finally, the wall, ceiling, and floor are drawn using helper functions.
 * 
 * @param	game		pointer to the game state
 * @param	ray_counter	index of the current ray being cast
 */
void	project_ray_into_3d(t_game *game, int ray_counter)
{
	t_wall	wall;

	game->ray->angle_diff = normalize_angle(game->ray->r_a - game->player->p_a);
	game->ray->dist_total *= cos(game->ray->angle_diff);
	wall.wall_height = (TILE_SIZE / game->ray->dist_total)
		* ((WIDTH / 2) / tan(game->player->fov_rd / 2));
	wall.wall_start = (HEIGHT / 2) - (wall.wall_height / 2);
	wall.wall_end = (HEIGHT / 2) + (wall.wall_height / 2);
	if (wall.wall_end > HEIGHT)
		wall.wall_end = HEIGHT;
	if (wall.wall_start < 0)
		wall.wall_start = 0;
	draw_wall(game, game->ray, ray_counter, wall);
	game->ray->color = game->map->clr_ceiling.rgba;
	draw_column(game, ray_counter, 0, wall.wall_start);
	game->ray->color = game->map->clr_floor.rgba;
	draw_column(game, ray_counter, wall.wall_end, HEIGHT);
}
