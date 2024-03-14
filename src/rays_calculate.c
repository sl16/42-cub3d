/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calculate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:28:25 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 15:30:48 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Calculates the distance between the player and the end of a ray.
 *
 * This function calculates the Euclidean distance between the player's position
 * and the end point of a ray. The Euclidean distance is calculated using
 * the formula sqrt((x2 - x1)^2 + (y2 - y1)^2), where (x1, y1) is the player's
 * position and (x2, y2) is the ray's end point.
 *
 * @param	p_x		player's x-coordinate
 * @param	p_y		player's y-coordinate
 * @param	r_x		ray's end x-coordinate
 * @param	r_y		ray's end y-coordinate
 * @return	double	the calculated distance
 */
static double	distance_player_ray_end(double p_x, double p_y, double r_x,
	double r_y)
{
	return (sqrt((r_x - p_x) * (r_x - p_x) + (r_y - p_y) * (r_y - p_y)));
}

/**
 * @brief	Checks if a given point (y, x) hits a wall in the map.
 *
 * The point's coordinates are first converted to map grid coordinates
 * by dividing by TILE_SIZE and flooring the result.
 *
 * @param	map	pointer to the map structure
 * @param	x	x-coordinate of the point
 * @param	y	y-coordinate of the point
 * @return	int	if the point is outside the map boundaries or hits a wall
 * 				(represented by '1' in the map grid), returns 0, otherwise 1
 */
static int	wall_hit(t_map *map, double x, double y)
{
	int	m_x;
	int	m_y;

	if (x < 0 || y < 0)
		return (0);
	m_x = floor (x / TILE_SIZE);
	m_y = floor (y / TILE_SIZE);
	if (m_y >= map->map_height || m_y < 0 || m_x >= map->map_width || m_x < 0)
		return (0);
	if (map->grid[m_y] && m_x < (int)strlen(map->grid[m_y]))
		if (map->grid[m_y][m_x] == '1')
			return (0);
	return (1);
}

/**
 * @brief	Checks if a ray has hit a wall.
 *
 * This function moves the ray step by step until it hits a wall. The direction
 * of the steps is determined by the orientation parameter.
 * 
 * If the orientation is HORIZONTAL, the function checks for a wall hit
 * at the horizontal intersection point (hx, hy) of the ray.
 * 
 * If a wall hit is detected, the function increments the intersection point
 * by the step size (x_step, y_step) and checks again. This process continues
 * until no wall hit is detected, meaning the ray has reached an open space.
 * 
 * If the orientation is VERTICAL, the function does the same but checks for
 * a wall hit at the vertical intersection point (vx, vy) of the ray.
 *
 * @param	map		pointer to the map structure
 * @param	ray		pointer to the ray structure
 * @param	orientation	the orientation of the ray (HORIZONTAL or VERTICAL)
 */
static void	reach_wall_hit(t_map *map, t_ray *ray, int orientation)
{
	if (orientation == HORIZONTAL)
	{
		while (wall_hit(map, ray->hx - ray->pixel, ray->hy))
		{
			ray->hx += ray->x_step;
			ray->hy += ray->y_step;
		}
	}
	else if (orientation == VERTICAL)
	{
		while (wall_hit(map, ray->vx, ray->vy - ray->pixel))
		{
			ray->vx += ray->x_step;
			ray->vy += ray->y_step;
		}
	}
}

/**
 * @brief	Calculates the vertical intersection of a ray with a wall.
 *
 * It first calculates the initial vertical intersection point (vx, vy) based
 * on the player's position and the ray's angle. The y-step size is set
 * to the size of a tile, and the x-step size is calculated based on the ray's
 * angle to ensure the ray moves at the correct angle.
 * 
 * If the ray is pointing upwards (angle between 0 and PI), the intersection
 * point is moved one tile up, and the pixel value is set to -1.
 * If the ray is pointing downwards (angle between PI and 2*PI), the y-step size
 * is inverted, and the pixel value is set to 1.
 * 
 * The function then checks for a wall hit at the intersection point and moves
 * the ray step by step until it hits a wall. After a wall hit is detected,
 * a small offset is added to the intersection point to avoid floating point
 * precision issues.
 * 
 * Finally, the function calculates the distance from the player
 * to the intersection point.
 *
 * @param	map		pointer to the map structure
 * @param	player	pointer to the player structure
 * @param	ray		pointer to the ray structure
 */
void	calculate_vertical_hit(t_map *map, t_player *player, t_ray *ray)
{
	ray->y_step = TILE_SIZE;
	ray->x_step = TILE_SIZE / tan(ray->angle_nor);
	ray->vy = floor(player->p_y / TILE_SIZE) * TILE_SIZE;
	if (ray->angle_nor > 0 && ray->angle_nor < M_PI)
	{
		ray->vy += TILE_SIZE;
		ray->pixel = -1;
	}
	else
	{
		ray->y_step *= (-1);
		ray->pixel = 1;
	}
	ray->vx = player->p_x + (ray->vy - player->p_y) / tan(ray->angle_nor);
	if (((ray->angle_nor > (M_PI / 2)
				&& ray->angle_nor < (3 * M_PI) / 2) && ray->x_step > 0)
		|| (!(ray->angle_nor > (M_PI / 2)
				&& ray->angle_nor < (3 * M_PI) / 2) && ray->x_step < 0))
		ray->x_step *= -1;
	reach_wall_hit(map, ray, VERTICAL);
	ray->vx += copysign(0.0001, ray->x_step);
	ray->vy += copysign(0.0001, ray->y_step);
	ray->dist_ver = distance_player_ray_end(player->p_x, player->p_y, ray->vx,
			ray->vy);
}

/**
 * @brief	Calculates the horizontal intersection of a ray with a wall.
 *
 * It first calculates the initial horizontal intersection point (hx, hy) based
 * on the player's position and the ray's angle. The x-step size is set
 * to the size of a tile, and the y-step size is calculated based on the ray's
 * angle to ensure the ray moves at the correct angle.
 * 
 * If the ray is pointing to the right (angle not between PI/2 and 3*PI/2),
 * the intersection point is moved one tile to the right, and the pixel value
 * is set to -1.
 * If the ray is pointing to the left (angle between PI/2 and 3*PI/2),
 * the x-step size is inverted, and the pixel value is set to 1.
 * 
 * The function then checks for a wall hit at the intersection point and moves
 * the ray step by step until it hits a wall. After a wall hit is detected,
 * a small offset is added to the intersection point to avoid floating point
 * precision issues.
 * 
 * Finally, the function calculates the distance from the player
 * to the intersection point.
 *
 * @param	map		pointer to the map structure
 * @param	player	pointer to the player structure
 * @param	ray		pointer to the ray structure
 */
void	calculate_horizontal_hit(t_map *map, t_player *player, t_ray *ray)
{
	ray->x_step = TILE_SIZE;
	ray->y_step = TILE_SIZE * tan(ray->angle_nor);
	ray->hx = floor(player->p_x / TILE_SIZE) * TILE_SIZE;
	if (!(ray->angle_nor > M_PI / 2 && ray->angle_nor < 3 * M_PI / 2))
	{
		ray->hx += TILE_SIZE;
		ray->pixel = -1;
	}
	else
	{
		ray->x_step *= (-1);
		ray->pixel = 1;
	}
	ray->hy = player->p_y + (ray->hx - player->p_x) * tan(ray->angle_nor);
	if (((ray->angle_nor > 0 && ray->angle_nor < M_PI) && ray->y_step < 0)
		|| (!(ray->angle_nor > 0 && ray->angle_nor < M_PI) && ray->y_step > 0))
		ray->y_step *= -1;
	reach_wall_hit(map, ray, HORIZONTAL);
	ray->hx += copysign(0.0001, ray->x_step);
	ray->hy += copysign(0.0001, ray->y_step);
	ray->dist_hor = distance_player_ray_end(player->p_x, player->p_y,
			ray->hx, ray->hy);
}
