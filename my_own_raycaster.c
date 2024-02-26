/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_own_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:48:33 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/26 13:47:07 aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

bool almost_equal(double a, double b, double epsilon)
{
	return (fabs(a - b) < epsilon);
}

bool almost_less_than(double a, double b, double epsilon) {
	return (b - a > epsilon);
}

bool almost_greater_than(double a, double b, double epsilon) {
	return (a - b > epsilon);
}

int	init_game_struct(t_game *game)
{
	game->map = calloc(1, sizeof(t_map));
	game->map->grid = calloc(9, sizeof(char *)); // init the map
	game->map->grid[0] = ft_strdup("11111111"); //fill the map
	game->map->grid[1] = ft_strdup("10100001");
	game->map->grid[2] = ft_strdup("10100001");
	game->map->grid[3] = ft_strdup("10100001");
	game->map->grid[4] = ft_strdup("10000001");
	game->map->grid[5] = ft_strdup("10000101");
	game->map->grid[6] = ft_strdup("10000001");
	game->map->grid[7] = ft_strdup("11111111");
	game->map->grid[8] = NULL;
	game->map->p_y = 3;
	game->map->p_x = 14;
	game->map->map_width = 8;
	game->map->map_height = 8;
	// Init player
	game->player = calloc(1, sizeof(t_player));
	game->player->p_a = 0; // player angle
	game->player->p_x = 300;
	game->player->p_y = 300;
	game->player->p_dx = cos(game->player->p_a) * 5;
	game->player->p_dy = sin(game->player->p_a) * 5;
	game->player->fov = (FOV * M_PI) / 180.0; // field of view in radians
	// Init ray	
	game->ray = calloc(1, sizeof(t_ray));
	game->ray->r_x = 0;
	game->ray->r_y = 0;
	game->ray->r_a = 0;
	game->ray->y_offset = 0;
	game->ray->x_offset = 0;
	return (0);
}

void	free_game_struct(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->map_height)
	{
		free(game->map->grid[i]);
		i++;
	}
	free(game->map->grid);
	free(game->map);
	free(game->player);
	free(game->ray);
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

void	handle_key_actions(void *param)
{
	t_game	    *game;
    t_player    *player;
	t_map		*map;
	// Wall colisions
	double		grid_x;
	double		grid_y;

	game = (t_game *) param;
    player = game->player;
	map = game->map;

	// Wall collisions
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_game_struct(game);
		exit(0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)) // move up
	{
		grid_x = player->p_x + player->p_dx; 
		grid_y = player->p_y + player->p_dy; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
    		player->p_x += player->p_dx; 
			player->p_y += player->p_dy; 
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)) // move down
	{
		grid_x = player->p_x - player->p_dx; 
		grid_y = player->p_y - player->p_dy; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
  	      player->p_x -= player->p_dx; 
  	      player->p_y -= player->p_dy; 
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) // move right
	{
		grid_x = player->p_x - player->p_dy; 
		grid_y = player->p_y + player->p_dx; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x -= player->p_dy; 
			player->p_y += player->p_dx; 
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) // move left
	{
		grid_x = player->p_x + player->p_dy; 
		grid_y = player->p_y - player->p_dx; 
		if (map->grid[(int)grid_y >> 6][(int)grid_x >> 6] == '0')
		{
			player->p_x += player->p_dy; 
			player->p_y -= player->p_dx; 
		}
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        player->p_a -= ROTATION_SPEED;
        if (almost_less_than(player->p_a, 0, PRECISION))
            player->p_a += 2 * M_PI;
        player->p_dx = cos(player->p_a) * 5;
        player->p_dy = sin(player->p_a) * 5;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        player->p_a += ROTATION_SPEED;
        if (almost_greater_than(player->p_a, (2 * M_PI), PRECISION))
            player->p_a -= 2 * M_PI;
        player->p_dx = cos(player->p_a) * 5;
        player->p_dy = sin(player->p_a) * 5;
    }
}

// Function that returs the distance between the player's position and the ray's end point
double	distance_player_ray_end(double p_x, double p_y, double r_x, double r_y)
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
		draw_line(player->p_x, player->p_y, ray->r_x, ray->r_y, 0xFF0000FF, game->image);
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
		draw_line_thickness(ray_counter * map->map_width + 530, (int)lineO, ray_counter * map->map_height + 530, (int)(lineH + lineO), color, 5, game->image);
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

void	draw(void *param)
{
	t_game	*game;
    t_player    *player;
	int		player_flag;

	game = (t_game *) param;
    player = game->player;
	player_flag = 0;
	// Draw background
	draw_square(game->image, 256, 256, HEIGHT, 0x000000FF); // black
	draw_square(game->image, 768, 256, HEIGHT, 0x000000FF); // black
    // Draw map grid
	draw_map_grid(game);
	// Draw lines in map grid
	draw_lines_in_map_grid(game);
	// Draw rays
	draw_rays(game, game->map, game->player, game->ray);
	// Draw player
	draw_square(game->image, (int)game->player->p_x, (int)game->player->p_y, PLAYER_SIZE, 0xFFFF00FF); // yellow
    // Draw a line to where the player is looking
	draw_line_thickness((int)player->p_x, (int)player->p_y, (int)(player->p_x + player->p_dx * 5),
		(int)(player->p_y + player->p_dy * 5), 0xFFFF00FF, 3, game->image);
}

int main(void)
{
	t_game	game;

	init_game_struct(&game);
	print_grid(game.map->grid, game.map->map_height);
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 1)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(&game);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, game.image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(&game);
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop_hook(game.mlx, handle_key_actions, &game);
	mlx_loop(game.mlx);
	free_game_struct(&game);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}

