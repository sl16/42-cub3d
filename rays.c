/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:22:05 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/26 17:25:00 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

// Function that returs the distance between the player's position and the ray's end point
static double	distance_player_ray_end(double p_x, double p_y, double r_x, double r_y)
{
	return (sqrt((r_x - p_x) * (r_x - p_x) + (r_y - p_y) * (r_y - p_y)));
}

void	draw_rays(t_game *game, t_map *map, t_player *player, t_ray *ray)
{
	int		ray_counter;
	int		dof;
	int		mx;
	int		my;
	double	distT;
	int		color;
	double	distH;
	double	hx; 
	double	hy;
	double	aTan;
	double	distV;
	double	vx; 
	double	vy;
	double	nTan;
	double	ca;
	double	lineH;
	double	lineO;
	t_draw_info	draw_info;

	// initialize ray angle DEGREE degrees back from the player angle
	ray->r_a = player->p_a - DEGREE * 30;
	// then we need to add the limits to the next angle bcs unit circle
	if (almost_less_than(ray->r_a, 0, PRECISION))
		ray->r_a += 2 * M_PI;
	if (almost_greater_than(ray->r_a, 2 * M_PI, PRECISION))
		ray->r_a -= 2 * M_PI;
	// how many rays will be drawn
	ray_counter = 0;
	while (ray_counter < FOV)
	{
		// HORIZONTAL
		// check horizontal lines - where the ray will first hit the closest horizontal line
		dof = 0;
		distH = 1000000000;
		hx = player->p_x;
		hy = player->p_y;
		aTan = -1 / tan(ray->r_a);
		if (almost_greater_than(ray->r_a, M_PI, PRECISION)) // ray looking up - determined from the ray angle
		{
			ray->r_y = (((int)player->p_y >> 6) << 6) - 0.0001;
			ray->r_x = (player->p_y - ray->r_y) * aTan + player->p_x;
			// once we have first ray hit position, we need next x and y offset
			ray->y_offset = (-TILE_SIZE);
			ray->x_offset = (-ray->y_offset) * aTan;
		}
		if (almost_less_than(ray->r_a, M_PI, PRECISION)) // ray looking down - determined from the ray angle
		{
			ray->r_y = (((int)player->p_y >> 6) << 6) + TILE_SIZE;
			ray->r_x = (player->p_y - ray->r_y) * aTan + player->p_x;
			// once we have first ray hit position, we need next x and y offset
			ray->y_offset = TILE_SIZE;
			ray->x_offset = (-ray->y_offset) * aTan;
		}
		if (almost_equal(ray->r_a, 0, PRECISION) || almost_equal(ray->r_a, M_PI, PRECISION)) // if the ray is looking straight left or right, it will never hit a horizontal line
		{
			ray->r_x = player->p_x;
			ray->r_y = player->p_y;
			dof = DOF;
		}
		while (dof < DOF)
		{
			mx = (int)(ray->r_x) >> 6;
			my = (int)(ray->r_y) >> 6;
			if (mx >= 0 && mx < map->map_width && my >= 0 && my < map->map_height && map->grid[my][mx] == '1') // hit wall
			{
				hx = ray->r_x;
				hy = ray->r_y;
				distH = distance_player_ray_end(player->p_x, player->p_y, hx, hy);
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
		distV = 1000000000;
		vx = player->p_x;
		vy = player->p_y;
		nTan = (-tan(ray->r_a));
		if (almost_greater_than(ray->r_a, (M_PI / 2), PRECISION) && almost_less_than(ray->r_a, (3 * M_PI / 2), PRECISION)) // ray looking left - determined from the ray angle
		{
			ray->r_x = (((int)player->p_x >> 6) << 6) - 0.0001;
			ray->r_y = (player->p_x - ray->r_x) * nTan + player->p_y;
			// once we have first ray hit position, we need next x and y offset
			ray->x_offset = (-TILE_SIZE);
			ray->y_offset = (-ray->x_offset) * nTan;
		}
		if (almost_less_than(ray->r_a, (M_PI / 2), PRECISION) || almost_greater_than(ray->r_a, (3 * M_PI / 2), PRECISION)) // ray looking right - determined from the ray angle
		{
			ray->r_x = (((int)player->p_x >> 6) << 6) + TILE_SIZE;
			ray->r_y = (player->p_x - ray->r_x) * nTan + player->p_y;
			// once we have first ray hit position, we need next x and y offset
			ray->x_offset = TILE_SIZE;
			ray->y_offset = (-ray->x_offset) * nTan;
		}
		if (almost_equal(ray->r_a, 0, PRECISION) || almost_equal(ray->r_a, M_PI, PRECISION)) // if the ray is looking straight up or down, it will never hit a vertical line
		{
			ray->r_x = player->p_x;
			ray->r_y = player->p_y;
			dof = DOF;
		}
		while (dof < DOF)
		{
			mx = (int)(ray->r_x) >> 6;
			my = (int)(ray->r_y) >> 6;
			if (mx >= 0 && mx < map->map_width && my >= 0 && my < map->map_height && map->grid[my][mx] == '1') // hit wall
			{
				vx = ray->r_x;
				vy = ray->r_y;
				distV = distance_player_ray_end(player->p_x, player->p_y, vx, vy);
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
		if (almost_less_than(distV, distH, PRECISION))
		{
			ray->r_x = vx;
			ray->r_y = vy;
			distT = distV;
			color = 0xFF0000FF;
		}
		else if (almost_less_than(distH, distV, PRECISION))
		{
			ray->r_x = hx;
			ray->r_y = hy;
			distT = distH;
			color = 0x913831FF;
		}
		draw_info.y1 = player->p_y;
		draw_info.x1 = player->p_x;
		draw_info.y2 = ray->r_y;
		draw_info.x2 = ray->r_x;
		draw_info.color = 0xFF0000FF;
		draw_line(game->image, draw_info);
		// 3D WALLS
		// distance between the player angle and the ray angle
		ca = player->p_a - ray->r_a;
		if (almost_less_than(ca, 0, PRECISION))
			ca += 2 * M_PI;
		if (almost_greater_than(ca, (2 * M_PI), PRECISION))
			ca -= 2 * M_PI;
		// multiply the ray distance by the cosine of that ray angle
		distT = distT * cos(ca); // fix fish eye
		lineH = (TILE_SIZE * 320) / distT; // line height
		if (almost_greater_than(lineH, 320, PRECISION))
			lineH = 320;
		lineO = 160 - lineH / 2; // line offset

		draw_info.y1 = lineO;
		draw_info.x1 = ray_counter * map->map_width + 530;
		draw_info.y2 = lineH + lineO;
		draw_info.x2 = ray_counter * map->map_height + 530;
		draw_info.size = 8;
		draw_info.color = color;
		draw_line_thickness(game->image, draw_info);

		// NEXT RAY setup
		// if drawing more lines, the angle need to move after each line
		ray->r_a += DEGREE;
		// and the limits need to be set again bcs unit circle
		if (almost_less_than(ray->r_a, 0, PRECISION))
			ray->r_a += 2 * M_PI;
		if (almost_greater_than(ray->r_a, 2 * M_PI, PRECISION))
			ray->r_a -= 2 * M_PI;
		ray_counter++;
	}
}
