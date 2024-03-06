/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:16:47 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/06 09:49:05 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Draws a square of a specified size and color on the given image.
 * 
 * The position of the square is determined by the draw_info parameter.
 * The square is drawn pixel by pixel, checking each pixel's position to ensure
 * it's within the image boundaries.
 *
 * @param	image		pointer to the image where the square is drawn
 * @param	draw_info	struct with the drawing info (position, size, color)
 */
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
			if (pxl_x >= 0 && pxl_x <= WIDTH && pxl_y >= 0 && pxl_y <= HEIGHT)
				mlx_put_pixel(image, pxl_x, pxl_y, draw_info.color);
			y++;
		}
		x++;
	}
}

/**
 * @brief	Calculates the deltas for drawing a line.
 *
 * This function calculates the differences in the x and y coordinates between
 * two points, as well as the length of the line between these points.
 * These values are used to draw a line.
 *
 * @param	draw_info		struct with the drawing info (start and end points)
 * @return	t_draw_delta	struct with deltas and the length of the line
 */
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

/**
 * @brief	Draws a line of a specified color on the given image.
 * 
 * The start and end points of the line are determined by the draw_info
 * parameter. The line is drawn pixel by pixel, checking each pixel's position
 * to ensure it's within the image boundaries.
 *
 * @param	image		pointer to the image where the line is drawn
 * @param	draw_info	struct with the drawing info (start, end color)
 */
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
		if (pxl_x >= 0 && pxl_x <= WIDTH && pxl_y >= 0 && pxl_y <= HEIGHT)
			mlx_put_pixel(image, pxl_x, pxl_y, draw_info.color);
		else
			break ;
		pxl_x += delta.delta_x;
		pxl_y += delta.delta_y;
		delta.length--;
	}
}

/**
 * @brief	Prints a grid to the console.
 *
 * @param	grid		pointer to the 2D array representing the grid
 * @param	map_height	the number of rows in the grid
 */
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
