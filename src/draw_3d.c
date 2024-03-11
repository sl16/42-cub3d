/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:14:29 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/12 00:09:33 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

// to be replaced in parser: function checking if the files exist via load_png + delete_texture (to free memory at the end too))
void	load_textures(t_map *map)
{
	map->mlx_txt_no = mlx_load_png(map->txt_no);	
	map->mlx_txt_so = mlx_load_png(map->txt_so);	
	map->mlx_txt_we = mlx_load_png(map->txt_we);	
	map->mlx_txt_ea = mlx_load_png(map->txt_ea);	
}

static	mlx_texture_t	*get_texture(t_map *map, t_ray *ray)
{
	if (ray->angle_orientation == HORIZONTAL)	
	{
		if (ray->angle_nor > M_PI / 2 && ray->angle_nor < 3 * (M_PI / 2))
			return (map->mlx_txt_so); // south
		else
			return (map->mlx_txt_no); // north
	}
	else if (ray->angle_orientation == VERTICAL)
	{
		if (ray->angle_nor > 0 && ray->angle_nor < M_PI)
			return (map->mlx_txt_ea); // east
		else
			return (map->mlx_txt_we); // west
	}
	return (0);
}

// replaced with draw_wall below
void	draw_wall_old(t_game *game, int x, double start, double stop)
{
	while (start < stop)
	{
		mlx_put_pixel(game->image, x, start, game->ray->color);
		start++;
	}
}

t_clr reverse_bytes(t_clr color)
{
	t_clr reversed_color;

	reversed_color.r = color.a;
	reversed_color.g = color.b;
	reversed_color.b = color.g;
	reversed_color.a = color.r;
	return (reversed_color);
}

void	draw_wall(t_game *game, t_ray *ray, int x, double wall_start, double wall_end, double wall_height)
{
	mlx_texture_t	*txt;
	double		txt_x;
	double		txt_y;
	double		txt_factor;
	t_clr		*txt_color_array;
	t_clr	color;

	// gets the texture for the wall, determined by the orientation and direction of the ray
	txt = get_texture(game->map, ray);
	// gets a point to the pixel data of the texture
	// each pixel is represented as a t_clr struct (rgba)
	// Details:
	// Pixels hold the raw pixels of the texture as a 1D array
	// each element of pixels (byte, bcs it's of type uint8_t) represents of pixel's colors (r, g, b or a)
	// When casted into t_clr (or uint32_t) each element represents one whole pixel as it can hold 4 bytes
	// this is done so that we can later directly access the color of the whole pixel that we are interested in
	txt_color_array = (t_clr *)txt->pixels;
	// Calculates the factor by which the texture should be scaled to fit the height of the wall
	// If the wall slice is taller than the texture, the texture will be stretched
	// If it's shorter, the texture will be squished
	txt_factor = (double)(floor(txt->height / TILE_SIZE) * TILE_SIZE) / wall_height;
	// the if-else statement determines the x-coordinate of the texture
	if (game->ray->angle_orientation ==  HORIZONTAL)	
	// When the ray hit the wall horizontally, it means it hit it at the y-coordinate
	// Fmod gets the exact position where the ray hit the wall on the y-axis relative to the size of a tile
	// that is done by taking the remainder of the division of ray->hy by TILE_SIZE, which effectively gives the y-coordinate within the bounds of the current tile
	// This value is then divided by TILE_SIZE to normalize it to a range between 0 and 1.
	// this is necessary because texture coordinates are typically defined in a range from 0 to 1, where 0 represents one edge of the texture and 1 represents the opposite edge.
	// Finally, this normalized value is multiplied by txt->width to scale it to the width of the texture
	// this gives the x-coordinate of the texture that corresponds to the point on the wall where the ray hit.
		txt_x = fmod(ray->r_y, TILE_SIZE) / TILE_SIZE * txt->width;
	else if (game->ray->angle_orientation == VERTICAL)
		txt_x = fmod(ray->r_x, TILE_SIZE) / TILE_SIZE * txt->width;
	// HEIGHT / 2 is used to adjust the y-coordinate to be relative to the middle of the screen (doesn't neccessarily mean that the wall will be in the middle)
	// Wall_height / 2 then offsets the starting point, so that half of the wall is drawn to the middle point and the other from it
	// Finally the scaling factor is used to get the y-coordinate of the texture that corresponds to the y-coordinate on the screen
	txt_y = ((wall_start - (HEIGHT / 2) + (wall_height / 2)) * txt_factor);
	while (wall_start < wall_end)
	{
		// Indexing:
		//  The texture's pixel data is stored in a one-dimensional array, but it represents a two-dimensional image.
		//  therefore, we need to convert the 2D coordinates (txt_x, txt_y) into a 1D index to access the correct pixel.
		//	Txt_y * txt->width finds the start of the row (first pixel) in the 1D array that corresponds to the y-coordinate on the texture
		//  + txt_x finds the x-coordinate within the row as it moves from the beginning of the row to the correct pixel
		// Reverse_bytes:
		//  
		color = reverse_bytes(txt_color_array[(int)txt_y * txt->width + (int)txt_x]);
		//color = txt_color_array[(int)txt_y * txt->width + (int)txt_x];
		mlx_put_pixel(game->image, x, wall_start, color.rgba);
		// Moves the y-coordinate ensuring that the texture is scaled to the height of the wall
		txt_y += txt_factor;
		wall_start++;
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
	//draw_wall_old(game, ray_counter, wall_start, wall_end);
	draw_wall(game, game->ray, ray_counter, wall_start, wall_end, wall_height);
	game->ray->color = reverse_bytes(game->map->clr_ceiling).rgba;
//	game->ray->color = game->map->clr_ceiling.rgba;
	draw_3d_column(game, ray_counter, 0, wall_start);
	game->ray->color = reverse_bytes(game->map->clr_floor).rgba;
//	game->ray->color = game->map->clr_floor.rgba;
	draw_3d_column(game, ray_counter, wall_end, HEIGHT);
}
