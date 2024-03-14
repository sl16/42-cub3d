/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:58:13 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 15:29:03 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief	Normalizes an angle to the range [0, 2*PI].
 *
 * If the angle is less than 0, it adds 2*PI to shift it to the [0, 2*PI] range.
 * If the angle is more than 2*PI, it subtracts 2*PI to shift it
 * to the [0, 2*PI] range.
 *
 * @param	angle	the angle to normalize
 * @return	double	the normalized angle
 */
double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

/**
 * @brief	Selects the shortest ray after horizontal and vertical intersections
 * have been calculated.
 *
 * If the horizontal distance is shorter, the total distance of the ray is set
 * to the horizontal distance, and the intersection point (r_x, r_y) is set
 * to the horizontal intersection point (hx, hy).
 * 
 * The color of the ray is also set based on the direction of the ray
 * to indicate a north or south wall hit.
 * If the vertical distance is shorter, the total distance of the ray is set
 * to the vertical distance, and the intersection point (r_x, r_y) is set
 * to the vertical intersection point (vx, vy).
 * 
 * @param	ray		pointer to the ray structure
 */
void	pick_shortest_ray(t_ray *ray)
{
	if (ray->dist_hor < ray->dist_ver)
	{
		ray->dist_total = ray->dist_hor;
		ray->angle_orientation = HORIZONTAL;
		ray->r_x = ray->hx;
		ray->r_y = ray->hy;
	}
	else
	{
		ray->dist_total = ray->dist_ver;
		ray->angle_orientation = VERTICAL;
		ray->r_x = ray->vx;
		ray->r_y = ray->vy;
	}
}

/**
 * @brief	Casts rays from the player's position in 3D.
 *
 * It first sets the initial ray angle to the player's angle minus half
 * of the field of view.
 * 
 * Then, for each column of the screen, it normalizes the ray angle,
 * calculates the vertical and horizontal intersections of the ray with a wall,
 * and selects the shortest ray. It then draws the 3D projection of the wall
 * on the screen.
 * 
 * Finally, it increments the ray angle by the field of view divided
 * by the screen width and repeats the process for the next column.
 *
 * @param	game	pointer to the game structure
 * @param	player	pointer to the player structure
 * @param	ray		pointer to the ray structure
 */

void	cast_rays_3d(t_game *game, t_player *player, t_ray *ray)
{
	int	ray_counter;

	ray->r_a = player->p_a - (player->fov_rd / 2);
	ray_counter = 0;
	while (ray_counter < WIDTH)
	{
		ray->angle_nor = normalize_angle(ray->r_a);
		calculate_vertical_hit(game->map, player, ray);
		calculate_horizontal_hit(game->map, player, ray);
		pick_shortest_ray(ray);
		project_ray_into_3d(game, ray_counter);
		ray->r_a += (player->fov_rd / WIDTH);
		ray_counter++;
	}
}
