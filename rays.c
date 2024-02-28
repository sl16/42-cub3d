/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:22:05 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/28 17:17:16 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

static double	distance_player_ray_end(double p_x, double p_y, double r_x,
	double r_y)
{
	return (sqrt((r_x - p_x) * (r_x - p_x) + (r_y - p_y) * (r_y - p_y)));
}

// then we need to add the limits to the next angle bcs unit circle
static double	limits_unit_circle(double num)
{
	if (almost_less_than(num, 0, PRECISION))
		num += 2 * M_PI;
	if (almost_greater_than(num, 2 * M_PI, PRECISION))
		num -= 2 * M_PI;
	return (num);
}

void	calculate_horizontal_hit()
{
	
}

// initialize ray angle DEGREE degrees back from the player angle
void	draw_rays(t_game *game, t_map *map, t_player *player, t_ray *ray)
{
	int		ray_counter;
	int		dof;
	int		color;
	t_draw_info			draw_info;
	t_ray_calculation	ray_cal;

	ray->r_a = player->p_a - DEGREE * 30;
	ray->r_a = limits_unit_circle(ray->r_a);
	ray_counter = 0;
	while (ray_counter < FOV)
	{
		// HORIZONTAL
		// check horizontal lines - where the ray will first hit the closest horizontal line
		dof = 0;
		ray_cal.dist_horizontal = 1000000000;
		ray_cal.hx = player->p_x;
		ray_cal.hy = player->p_y;
		ray_cal.tan_pos = -1 / tan(ray->r_a);
		if (almost_greater_than(ray->r_a, M_PI, PRECISION)) // ray looking up - determined from the ray angle
		{
			ray->r_y = (((int)player->p_y >> 6) << 6) - 0.0001;
			ray->r_x = (player->p_y - ray->r_y) * ray_cal.tan_pos + player->p_x;
			// once we have first ray hit position, we need next x and y offset
			ray->y_offset = (-TILE_SIZE);
			ray->x_offset = (-ray->y_offset) * ray_cal.tan_pos;
		}
		if (almost_less_than(ray->r_a, M_PI, PRECISION)) // ray looking down - determined from the ray angle
		{
			ray->r_y = (((int)player->p_y >> 6) << 6) + TILE_SIZE;
			ray->r_x = (player->p_y - ray->r_y) * ray_cal.tan_pos + player->p_x;
			// once we have first ray hit position, we need next x and y offset
			ray->y_offset = TILE_SIZE;
			ray->x_offset = (-ray->y_offset) * ray_cal.tan_pos;
		}
		if (almost_equal(ray->r_a, 0, PRECISION) || almost_equal(ray->r_a, M_PI, PRECISION)) // if the ray is looking straight left or right, it will never hit a horizontal line
		{
			ray->r_x = player->p_x;
			ray->r_y = player->p_y;
			dof = DOF;
		}
		while (dof < DOF)
		{
			ray_cal.mx = (int)(ray->r_x) >> 6;
			ray_cal.my = (int)(ray->r_y) >> 6;
			if (ray_cal.mx >= 0 && ray_cal.mx < map->map_width && ray_cal.my >= 0 && ray_cal.my < map->map_height && map->grid[ray_cal.my][ray_cal.mx] == '1') // hit wall
			{
				ray_cal.hx = ray->r_x;
				ray_cal.hy = ray->r_y;
				ray_cal.dist_horizontal = distance_player_ray_end(player->p_x, player->p_y, ray_cal.hx, ray_cal.hy);
				dof = DOF;
			}
			else
			{
				ray->r_x += ray->x_offset;
				ray->r_y += ray->y_offset;
				dof += 1;
			}
		}
	//	draw_line(player->p_x, player->p_y, ray->r_x, ray->r_y, 0x00FF00FF, game->image);
		
		// VERTICAL
		// check vertical lines - where the ray will first hit the closest vertical line
		dof = 0;
		ray_cal.dist_vertical = 1000000000;
		ray_cal.vx = player->p_x;
		ray_cal.vy = player->p_y;
		ray_cal.tan_neg = (-tan(ray->r_a));
		if (almost_greater_than(ray->r_a, (M_PI / 2), PRECISION) && almost_less_than(ray->r_a, (3 * M_PI / 2), PRECISION)) // ray looking left - determined from the ray angle
		{
			ray->r_x = (((int)player->p_x >> 6) << 6) - 0.0001;
			ray->r_y = (player->p_x - ray->r_x) * ray_cal.tan_neg + player->p_y;
			// once we have first ray hit position, we need next x and y offset
			ray->x_offset = (-TILE_SIZE);
			ray->y_offset = (-ray->x_offset) * ray_cal.tan_neg;
		}
		if (almost_less_than(ray->r_a, (M_PI / 2), PRECISION) || almost_greater_than(ray->r_a, (3 * M_PI / 2), PRECISION)) // ray looking right - determined from the ray angle
		{
			ray->r_x = (((int)player->p_x >> 6) << 6) + TILE_SIZE;
			ray->r_y = (player->p_x - ray->r_x) * ray_cal.tan_neg + player->p_y;
			// once we have first ray hit position, we need next x and y offset
			ray->x_offset = TILE_SIZE;
			ray->y_offset = (-ray->x_offset) * ray_cal.tan_neg;
		}
		if (almost_equal(ray->r_a, 0, PRECISION) || almost_equal(ray->r_a, M_PI, PRECISION)) // if the ray is looking straight up or down, it will never hit a vertical line
		{
			ray->r_x = player->p_x;
			ray->r_y = player->p_y;
			dof = DOF;
		}
		while (dof < DOF)
		{
			ray_cal.mx = (int)(ray->r_x) >> 6;
			ray_cal.my = (int)(ray->r_y) >> 6;
			if (ray_cal.mx >= 0 && ray_cal.mx < map->map_width && ray_cal.my >= 0 && ray_cal.my < map->map_height && map->grid[ray_cal.my][ray_cal.mx] == '1') // hit wall
			{
				ray_cal.vx = ray->r_x;
				ray_cal.vy = ray->r_y;
				ray_cal.dist_vertical = distance_player_ray_end(player->p_x, player->p_y, ray_cal.vx, ray_cal.vy);
				dof = DOF;
			}
			else
			{
				ray->r_x += ray->x_offset;
				ray->r_y += ray->y_offset;
				dof += 1;
			}
		}
	//	draw_line(player->p_x, player->p_y, ray->r_x, ray->r_y, 0x00FF00FF, game->image);
		// pick the shortest distance
		if (almost_less_than(ray_cal.dist_vertical, ray_cal.dist_horizontal, PRECISION))
		{
			ray->r_x = ray_cal.vx;
			ray->r_y = ray_cal.vy;
			ray_cal.dist_total = ray_cal.dist_vertical;
			color = 0x913831FF;
		}
		else if (almost_less_than(ray_cal.dist_horizontal, ray_cal.dist_vertical, PRECISION))
		{
			ray->r_x = ray_cal.hx;
			ray->r_y = ray_cal.hy;
			ray_cal.dist_total = ray_cal.dist_horizontal;
			color = 0xFF0000FF;
		}
		draw_info.y1 = player->p_y;
		draw_info.x1 = player->p_x;
		draw_info.y2 = ray->r_y;
		draw_info.x2 = ray->r_x;
		draw_info.color = 0xFF0000FF;
		draw_line(game->image, draw_info);
		// 3D WALLS
		// distance between the player angle and the ray angle
		ray_cal.angle_diff = player->p_a - ray->r_a;
		ray_cal.angle_diff = limits_unit_circle(ray_cal.angle_diff);
		// multiply the ray distance by the cosine of that ray angle
		ray_cal.dist_total = ray_cal.dist_total * cos(ray_cal.angle_diff); // fix fish eye
		ray_cal.line_height = (TILE_SIZE * 320) / ray_cal.dist_total; // line height
		if (almost_greater_than(ray_cal.line_height, 320, PRECISION))
			ray_cal.line_height = 320;
		ray_cal.line_offset = 160 - ray_cal.line_height / 2; // line offset

		draw_info.y1 = ray_cal.line_offset;
		draw_info.x1 = ray_counter * map->map_width + 530;
		draw_info.y2 = ray_cal.line_height + ray_cal.line_offset;
		draw_info.x2 = ray_counter * map->map_height + 530;
		draw_info.size = 8;
		draw_info.color = color;
		draw_line_thickness(game->image, draw_info);

		// NEXT RAY setup
		// if drawing more lines, the angle need to move after each line
		ray->r_a += DEGREE;
		ray->r_a = limits_unit_circle(ray->r_a);
		ray_counter++;
	}
}