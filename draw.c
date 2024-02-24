/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:39:23 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/24 16:51:43 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"



void	draw_square(mlx_image_t *image, int p_x, int p_y, int size, uint32_t color)
{
	int	x;
	int	y;
	int pixel_x;
	int pixel_y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			pixel_x = (p_x - size / 2) + x;
			pixel_y = (p_y - size / 2) + y;

			if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
				mlx_put_pixel(image, pixel_x, pixel_y, color);
			y++;
		}
		x++;
	}
}

void	draw_line(int x1, int y1, int x2, int y2, uint32_t color, mlx_image_t *image)
{
	int		length;
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	length = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	delta_x /= length;
	delta_y /= length;
	pixel_x = x1;
	pixel_y = y1;
	while (length)
	{
		if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
			mlx_put_pixel(image, (int)pixel_x, (int)pixel_y, color);
		else
			break ;
		pixel_x += delta_x;
		pixel_y += delta_y;
		length--;
	}
}

void draw_line_thickness(int x1, int y1, int x2, int y2, uint32_t color, int thickness, mlx_image_t *image)
{
	int		length;
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	length = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	delta_x /= length;
	delta_y /= length;

	for (int t = -thickness / 2; t < thickness / 2; ++t) {
		pixel_x = x1 + t * -delta_y;
		pixel_y = y1 + t * delta_x;
		int p = length;
		while (p)
		{
			if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
				mlx_put_pixel(image, (int)pixel_x, (int)pixel_y, color);
			pixel_x += delta_x;
			pixel_y += delta_y;
			p--;
		}
	}
}

void    draw_map_grid(t_game *game)
{
    int i;
    int j;
    int y;
    int x;

	i = 0;
	y = TILE_SIZE / 2;
    while (game->map->grid[i])
    {
	    x = TILE_SIZE / 2;
        j = 0;
    	while (game->map->grid[i][j])
    	{
    		if (game->map->grid[i][j] == '1')
    			draw_square(game->image, x, y, TILE_SIZE, 0xFFFFFFFF); // white
    		else if (game->map->grid[i][j] == '0')
    			draw_square(game->image, x, y, TILE_SIZE, 0xB99470FF); // brown
    		x += TILE_SIZE;
    		j++;
    	}
    	y += TILE_SIZE;
        i++;
    }
}

void    draw_lines_in_map_grid(t_game *game)
{
    int i;
    int y;
    int x;
	// vertical
	y = 0;
	x = TILE_SIZE;
    i = 0;
	while (i < game->map->map_height)
	{
			draw_line(x, y, x, y + (TILE_SIZE * game->map->map_height), 0x000000FF, game->image); // black
			x += TILE_SIZE;
            i++;
	}
	// horizontal
	y = TILE_SIZE;
	x = 0;
    i = 0;
	while (i < game->map->map_width)
	{
			draw_line(x, y, x + (TILE_SIZE * game->map->map_width), y, 0x000000FF, game->image); // black
			y += TILE_SIZE;
            i++;
	}
}