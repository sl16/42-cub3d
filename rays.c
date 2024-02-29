/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:22:05 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/29 16:40:13 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

static double	distance_player_ray_end(double p_x, double p_y, double r_x,
	double r_y)
{
	return (sqrt((r_x - p_x) * (r_x - p_x) + (r_y - p_y) * (r_y - p_y)));
}

static double	limits_unit_circle(double num)
{
	if (almost_less_than(num, 0, PRECISION))
		num += 2 * M_PI;
	if (almost_greater_than(num, 2 * M_PI, PRECISION))
		num -= 2 * M_PI;
	return (num);
}

static void	reach_horizontal_hit_loop(t_ray_calculation *ray_cal, t_map *map,
	t_player *player, t_ray *ray)
{
	while (ray_cal->dof < DOF)
	{
		ray_cal->mx = (int)(ray->r_x) >> 6;
		ray_cal->my = (int)(ray->r_y) >> 6;
		if (ray_cal->mx >= 0 && ray_cal->mx < map->map_width
			&& ray_cal->my >= 0 && ray_cal->my < map->map_height
			&& map->grid[ray_cal->my][ray_cal->mx] == '1')
		{
			ray_cal->hx = ray->r_x;
			ray_cal->hy = ray->r_y;
			ray_cal->dist_hor = distance_player_ray_end(player->p_x,
					player->p_y, ray_cal->hx, ray_cal->hy);
			ray_cal->dof = DOF;
		}
		else
		{
			ray->r_x += ray->x_offset;
			ray->r_y += ray->y_offset;
			ray_cal->dof += 1;
		}
	}
}

static void	horizontal_hit_direction(t_ray_calculation *ray_cal,
	t_player *player, t_ray *ray)
{
	ray_cal->tan_pos = -1 / tan(ray->r_a);
	if (almost_greater_than(ray->r_a, M_PI, PRECISION))
	{
		ray->r_y = (((int)player->p_y >> 6) << 6) - 0.0001;
		ray->r_x = (player->p_y - ray->r_y) * ray_cal->tan_pos + player->p_x;
		ray->y_offset = (-TILE_SIZE);
		ray->x_offset = (-ray->y_offset) * ray_cal->tan_pos;
	}
	if (almost_less_than(ray->r_a, M_PI, PRECISION))
	{
		ray->r_y = (((int)player->p_y >> 6) << 6) + TILE_SIZE;
		ray->r_x = (player->p_y - ray->r_y) * ray_cal->tan_pos + player->p_x;
		ray->y_offset = TILE_SIZE;
		ray->x_offset = (-ray->y_offset) * ray_cal->tan_pos;
	}
	if (almost_equal(ray->r_a, 0, PRECISION)
		|| almost_equal(ray->r_a, M_PI, PRECISION))
	{
		ray->r_x = player->p_x;
		ray->r_y = player->p_y;
		ray_cal->dof = DOF;
	}
}

/**
 * @brief	This function calculates the horizontal hit of a ray in a grid-based
 * map. It uses a ray casting algorithm to find the closest wall hit by the ray.
 *
 * The function first initializes the distance to the horizontal hit to a large
 * number, and the hit coordinates to the player's position.
 *
 * It then checks the direction of the ray (up or down) based on its angle,
 * and calculates the first hit position and the x and y offsets for the next
 * hit positions.
 * If the ray is looking straight left or right, it will never hit a horizontal
 * line, so the hit position is set to the player's position and
 * the Depth of Field (dof) is set to its maximum value.
 *
 * The function then enters a loop that continues until the ray hits a wall or
 * the dof reaches its maximum value. In each iteration of the loop, it checks
 * if the ray has hit a wall. If it as, it updates the hit coordinates and
 * the distance to the hit, and sets dof to its maximum value to end the loop.
 * If the ray has not hit a wall, it moves the ray to the next hit position
 * (via ray offset) and increments dof.
 * 
 * @param	ray_cal	struct with variables used in the ray calculation
 * @param	map		struct reprsenting the map of the game
 * @param	player	struct epresenting the player in the game
 * @param	ray		struct representing the ray being cast
 */
void	calculate_horizontal_hit(t_ray_calculation *ray_cal, t_map *map,
	t_player *player, t_ray *ray)
{
	ray_cal->dof = 0;
	ray_cal->dist_hor = 1000000000;
	ray_cal->hx = player->p_x;
	ray_cal->hy = player->p_y;
	horizontal_hit_direction(ray_cal, player, ray);
	reach_horizontal_hit_loop(ray_cal, map, player, ray);
//	draw_line(player->p_x, player->p_y, ray->r_x, ray->r_y, 0x00FF00FF,	game->image);
}

static void	reach_vertical_hit_loop(t_ray_calculation *ray_cal, t_map *map,
	t_player *player, t_ray *ray)
{
	while (ray_cal->dof < DOF)
	{
		ray_cal->mx = (int)(ray->r_x) >> 6;
		ray_cal->my = (int)(ray->r_y) >> 6;
		if (ray_cal->mx >= 0 && ray_cal->mx < map->map_width
			&& ray_cal->my >= 0 && ray_cal->my < map->map_height
			&& map->grid[ray_cal->my][ray_cal->mx] == '1')
		{
			ray_cal->vx = ray->r_x;
			ray_cal->vy = ray->r_y;
			ray_cal->dist_ver = distance_player_ray_end(player->p_x,
					player->p_y, ray_cal->vx, ray_cal->vy);
			ray_cal->dof = DOF;
		}
		else
		{
			ray->r_x += ray->x_offset;
			ray->r_y += ray->y_offset;
			ray_cal->dof += 1;
		}
	}
}

static void	vertical_hit_direction(t_ray_calculation *ray_cal, t_player *player,
	t_ray *ray)
{
	ray_cal->tan_neg = (-tan(ray->r_a));
	if (almost_greater_than(ray->r_a, (M_PI / 2), PRECISION)
		&& almost_less_than(ray->r_a, (3 * M_PI / 2), PRECISION))
	{
		ray->r_x = (((int)player->p_x >> 6) << 6) - 0.0001;
		ray->r_y = (player->p_x - ray->r_x) * ray_cal->tan_neg + player->p_y;
		ray->x_offset = (-TILE_SIZE);
		ray->y_offset = (-ray->x_offset) * ray_cal->tan_neg;
	}
	if (almost_less_than(ray->r_a, (M_PI / 2), PRECISION)
		|| almost_greater_than(ray->r_a, (3 * M_PI / 2), PRECISION))
	{
		ray->r_x = (((int)player->p_x >> 6) << 6) + TILE_SIZE;
		ray->r_y = (player->p_x - ray->r_x) * ray_cal->tan_neg + player->p_y;
		ray->x_offset = TILE_SIZE;
		ray->y_offset = (-ray->x_offset) * ray_cal->tan_neg;
	}
	if (almost_equal(ray->r_a, 0, PRECISION)
		|| almost_equal(ray->r_a, M_PI, PRECISION))
	{
		ray->r_x = player->p_x;
		ray->r_y = player->p_y;
		ray_cal->dof = DOF;
	}
}

/**
 * This function calculates the vertical hit of a ray in a grid-based map.
 * It uses a ray casting algorithm to find the closest wall hit by the ray.
 *
 * The function first initializes the distance to the vertical hit to a large
 * number, and the hit coordinates to the player's position.
 *
 * It then checks the direction of the ray (left or right) based on its angle,
 * and calculates the first hit position and the x and y offsets for the next
 * hit positions.
 *
 * If the ray is looking straight up or down, it will never hit a vertical line,
 * so the hit position is set to the player's position and the Depth of Field
 * (dof) is set to its maximum value.
 *
 * The function then enters a loop that continues until the ray hits a wall or
 * the dof reaches its maximum value. In each iteration of the loop, it checks
 * if the ray has hit a wall. If it has, it updates the hit coordinates and
 * the distance to the hit, and sets the dof to its maximum value to end
 * the loop. If the ray has not hit a wall, it moves the ray to the next hit
 * position (via ray offset) and increments the dof.
 * 
 * @param	ray_cal	struct with variables used in the ray calculation
 * @param	map		struct reprsenting the map of the game
 * @param	player	struct epresenting the player in the game
 * @param	ray		struct representing the ray being cast
 */
void	calculate_vertical_hit(t_ray_calculation *ray_cal, t_map *map,
	t_player *player, t_ray *ray)
{
	ray_cal->dof = 0;
	ray_cal->dist_ver = 1000000000;
	ray_cal->vx = player->p_x;
	ray_cal->vy = player->p_y;
	vertical_hit_direction(ray_cal, player, ray);
	reach_vertical_hit_loop(ray_cal, map, player, ray);
//	draw_line(player->p_x, player->p_y, ray->r_x, ray->r_y, 0x00FF00FF, game->image);
}

/**
 * @brief	This function picks the shortest ray between the horizontal and
 * vertical rays.
 * 
 * (needed for 2D drawing)
 * It updates the ray's x and y coordinates, the total distance, and the color
 * based on which ray is shorter.
 * 
 * (needed for 3D drawing)
 * It also calculates the difference between the player's angle and the ray's
 * angle, adjusts the total distance based on this angle difference, and
 * calculates the height and offset of the line to be drawn based
 * on the total distance.
 * 
 * @param	ray_cal	struct with variables used in the ray calculation
 * @param	player	struct epresenting the player in the game
 * @param	ray		struct representing the ray being cast
 */
void	pick_shortest_ray(t_ray_calculation *ray_cal, t_player *player,
	t_ray *ray)
{
	if (almost_less_than(ray_cal->dist_ver, ray_cal->dist_hor, PRECISION))
	{
		ray->r_x = ray_cal->vx;
		ray->r_y = ray_cal->vy;
		ray_cal->dist_total = ray_cal->dist_ver;
		ray->color = 0x913831FF;
	}
	else if (almost_less_than(ray_cal->dist_hor, ray_cal->dist_ver, PRECISION))
	{
		ray->r_x = ray_cal->hx;
		ray->r_y = ray_cal->hy;
		ray_cal->dist_total = ray_cal->dist_hor;
		ray->color = 0xFF0000FF;
	}
	ray_cal->angle_diff = player->p_a - ray->r_a;
	ray_cal->angle_diff = limits_unit_circle(ray_cal->angle_diff);
	ray_cal->dist_total = ray_cal->dist_total * cos(ray_cal->angle_diff);
	ray_cal->line_height = (TILE_SIZE * HEIGHT) / ray_cal->dist_total;
	if (almost_greater_than(ray_cal->line_height, HEIGHT, PRECISION))
		ray_cal->line_height = HEIGHT;
	ray_cal->line_offset = HEIGHT / 2 - ray_cal->line_height / 2;
}

void	draw_ray_2d(mlx_image_t *image, t_player *player, t_ray *ray)
{
	t_draw_info			draw_info;

	draw_info.y1 = player->p_y / MINI_MAP;
	draw_info.x1 = player->p_x  / MINI_MAP;
	draw_info.y2 = ray->r_y / MINI_MAP;
	draw_info.x2 = ray->r_x / MINI_MAP;
	draw_info.color = ray->color;
	draw_line(image, draw_info);
}

void	draw_ray_3d(t_game *game, t_ray_calculation *ray_cal, t_ray *ray,
	int ray_counter)
{
	t_draw_info			draw_info;

	draw_info.y1 = ray_cal->line_offset;
	draw_info.x1 = ray_counter * game->map->map_width + 330;
	draw_info.y2 = ray_cal->line_height + ray_cal->line_offset;
	draw_info.x2 = ray_counter * game->map->map_height + 330;
	draw_info.size = 8;
	draw_info.color = ray->color;
	draw_line_thickness(game->image, draw_info);
}

/**
 * @brief	This function draws all the rays for a given player's angle.
 * 
 * It initializes the ray's angle to 30 degrees back from the player's angle,
 * and then enters a loop that continues for the field of view (FOV).
 * 
 * In each iteration of the loop, it calculates the horizontal and vertical
 * hits of the ray, picks the shortest ray, and draws the 2D and 3D
 * representations of the ray. It then increments the ray's angle and
 * the ray counter.
 */
void	draw_rays(t_game *game, t_map *map, t_player *player, t_ray *ray)
{
	int					ray_counter;
	t_ray_calculation	ray_cal;

	ray->r_a = player->p_a - (M_PI / 180.0) * (FOV / 2.0);
	ray->r_a = limits_unit_circle(ray->r_a);
	ray_counter = 0;
	while (ray_counter < FOV)
	{
		calculate_horizontal_hit(&ray_cal, map, player, ray);
		calculate_vertical_hit(&ray_cal, map, player, ray);
		pick_shortest_ray(&ray_cal, player, ray);
		draw_ray_2d(game->image, player, ray);
		draw_ray_3d(game, &ray_cal, ray, ray_counter);
		ray->r_a += game->degree;
		ray->r_a = limits_unit_circle(ray->r_a);
		ray_counter++;
	}
}
