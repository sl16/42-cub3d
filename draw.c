/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:39:23 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/26 18:01:43 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	draw_square(mlx_image_t *image, t_draw_info draw_info)
{
	int	x;
	int	y;
	int	pxl_x;
	int	pxl_y;

	x = 0;
	while (x < draw_info.size)
	{
		y = 0;
		while (y < draw_info.size)
		{
			pxl_x = (draw_info.x1 - draw_info.size / 2) + x;
			pxl_y = (draw_info.y1 - draw_info.size / 2) + y;
			if (pxl_x >= 0 && pxl_x < WIDTH && pxl_y >= 0 && pxl_y < HEIGHT)
				mlx_put_pixel(image, pxl_x, pxl_y, draw_info.color);
			y++;
		}
		x++;
	}
}

static t_draw_delta	calculate_deltas(t_draw_info draw_info)
{
	t_draw_delta	delta;

	delta.delta_x = draw_info.x2 - draw_info.x1;
	delta.delta_y = draw_info.y2 - draw_info.y1;
	delta.length = sqrt(pow(delta.delta_x, 2) + pow(delta.delta_y, 2));
	delta.delta_x /= delta.length;
	delta.delta_y /= delta.length;
	return (delta);
}

void	draw_line(mlx_image_t *image, t_draw_info draw_info)
{
	t_draw_delta	delta;
	double			pxl_x;
	double			pxl_y;

	delta = calculate_deltas(draw_info);
	pxl_x = draw_info.x1;
	pxl_y = draw_info.y1;
	while (delta.length)
	{
		if (pxl_x >= 0 && pxl_x < WIDTH && pxl_y >= 0 && pxl_y < HEIGHT)
			mlx_put_pixel(image, pxl_x, pxl_y, draw_info.color);
		else
			break ;
		pxl_x += delta.delta_x;
		pxl_y += delta.delta_y;
		delta.length--;
	}
}

void	draw_line_thickness(mlx_image_t *image, t_draw_info draw_info)
{
	t_draw_delta	delta;
	double			pxl_x;
	double			pxl_y;
	int				size;
	int				pxls_draw;

	delta = calculate_deltas(draw_info);
	size = -draw_info.size / 2;
	while (size <= draw_info.size / 2 - 1)
	{
		pxl_x = draw_info.x1 + size * (-delta.delta_y);
		pxl_y = draw_info.y1 + size * delta.delta_x;
		pxls_draw = delta.length;
		while (pxls_draw)
		{
			if (pxl_x >= 0 && pxl_x < WIDTH && pxl_y >= 0 && pxl_y < HEIGHT)
				mlx_put_pixel(image, pxl_x, pxl_y, draw_info.color);
			pxl_x += delta.delta_x;
			pxl_y += delta.delta_y;
			pxls_draw--;
		}
		size++;
	}
}

void	draw_map_grid(t_game *game)
{
	int			i;
	int			j;
	int			y;
	int			x;
	t_draw_info	draw_info;

	i = 0;
	y = TILE_SIZE / 2;
	while (game->map->grid[i])
	{
		x = TILE_SIZE / 2;
		j = 0;
		while (game->map->grid[i][j])
		{
			draw_info.y1 = y;
			draw_info.x1 = x;
			draw_info.size = TILE_SIZE;
			if (game->map->grid[i][j] == '1')
				draw_info.color = 0xFFFFFFFF;
			else if (game->map->grid[i][j] == '0')
				draw_info.color = 0xB99470FF;
			draw_square(game->image, draw_info);
			x += TILE_SIZE;
			j++;
		}
		y += TILE_SIZE;
		i++;
	}
}

void	draw_lines_in_map_grid(t_game *game)
{
	int			i;
	t_draw_info	draw_info;

	i = 0;
	draw_info.y1 = 0;
	draw_info.x1 = TILE_SIZE;
	while (i < game->map->map_height)
	{
		draw_info.y2 = TILE_SIZE * game->map->map_height + draw_info.y1;
		draw_info.x2 = draw_info.x1;
		draw_info.color = 0x000000FF;
		draw_line(game->image, draw_info);
		draw_info.x1 += TILE_SIZE;
		i++;
	}
	draw_info.y1 = TILE_SIZE;
	draw_info.x1 = 0;
	i = 0;
	while (i < game->map->map_width)
	{
		draw_info.y2 = draw_info.y1;
		draw_info.x2 = TILE_SIZE * game->map->map_width + draw_info.x1;
		draw_info.color = 0x000000FF;
		draw_line(game->image, draw_info);
		draw_info.y1 += TILE_SIZE;
		i++;
	}
}

void	print_grid(char **grid, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		ft_printf("%s\n", grid[i]);
		i++;
	}
}
