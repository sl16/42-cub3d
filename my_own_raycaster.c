/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_own_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:48:33 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/22 17:28:44 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

int	init_game_struct(t_game *game)
{
	game->map = calloc(1, sizeof(t_map));
	game->map->grid = calloc(9, sizeof(char *)); // init the map
	game->map->grid[0] = ft_strdup("11111111"); //fill the map
	game->map->grid[1] = ft_strdup("10000001");
	game->map->grid[2] = ft_strdup("10101111");
	game->map->grid[3] = ft_strdup("11001001");
	game->map->grid[4] = ft_strdup("10000001");
	game->map->grid[5] = ft_strdup("10000001");
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

	game = (t_game *) param;
    player = game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_game_struct(game);
		exit(0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)) // move up
	{
		//player->p_y -= 5;
        player->p_x += player->p_dx; 
        player->p_y += player->p_dy; 
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)) // move down
	{
		//player->p_y += 5;
        player->p_x -= player->p_dx; 
        player->p_y -= player->p_dy; 
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) // move right
	{
		player->p_x -= player->p_dy; 
		player->p_y += player->p_dx; 
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) // move left
	{
		player->p_x += player->p_dy; 
		player->p_y -= player->p_dx; 
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        player->p_a -= ROTATION_SPEED;
        if (player->p_a < 0)
            player->p_a += 2 * M_PI;
        player->p_dx = cos(player->p_a) * 5;
        player->p_dy = sin(player->p_a) * 5;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        player->p_a += ROTATION_SPEED;
        if (player->p_a > 2 * M_PI)
            player->p_a -= 2 * M_PI;
        player->p_dx = cos(player->p_a) * 5;
        player->p_dy = sin(player->p_a) * 5;
    }
//    if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
//    {
//        player->p_x += player->p_dx; 
//        player->p_y += player->p_dy; 
//    }
//    if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
//    {
//        player->p_x -= player->p_dx; 
//        player->p_y -= player->p_dy; 
//    }
}

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
//	int dx = abs(x2 - x1);
//	int dy = abs(y2 - y1);
//	int sx = (x1 < x2) ? 1 : -1;
//	int sy = (y1 < y2) ? 1 : -1;
//	int err = dx - dy;
//
//	while (1) {
//		if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
//			mlx_put_pixel(image, x1, y1, color); // yellow
//		if ((x1 == x2 && y1 == y2) || x1 > WIDTH || y1 > HEIGHT) {
//			break;
//		}
//		int e2 = 2 * err;
//		if (e2 > -dy) {
//			err -= dy;
//			x1 += sx;
//		}
//		if (e2 < dx) {
//			err += dx;
//			y1 += sy;
//		}
//	}
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	pixels = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = x1;
	pixel_y = y1;
	while (pixels)
	{
		if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
			mlx_put_pixel(image, (int)pixel_x, (int)pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

void draw_line_thickness(int x1, int y1, int x2, int y2, uint32_t color, int thickness, mlx_image_t *image)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	pixels = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	delta_x /= pixels;
	delta_y /= pixels;

	for (int t = -thickness / 2; t < thickness / 2; ++t) {
		pixel_x = x1 + t * -delta_y;
		pixel_y = y1 + t * delta_x;
		int p = pixels;
		while (p)
		{
			if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
				mlx_put_pixel(image, (int)pixel_x, (int)pixel_y, color);
			pixel_x += delta_x;
			pixel_y += delta_y;
			p--;
		}
	}
//	int dx = abs(x2 - x1);
//	int dy = abs(y2 - y1);
//	int sx = (x1 < x2) ? 1 : -1;
//	int sy = (y1 < y2) ? 1 : -1;
//	int err = dx - dy;
//
//	int offset = thickness / 2;
//	int i;
//
//	for (i = -offset; i < offset; i++) {
//		int nx1 = x1, ny1 = y1, nx2 = x2, ny2 = y2;
//
//		if (dx > dy) {
//			ny1 += i;
//			ny2 += i;
//		} else {
//			nx1 += i;
//			nx2 += i;
//		}
//
//		while (1) {
//			if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
//				mlx_put_pixel(image, nx1, ny1, color);
//			if (nx1 == nx2 && ny1 == ny2) {
//				break;
//			}
//			int e2 = 2 * err;
//			if (e2 > -dy) {
//				err -= dy;
//				nx1 += sx;
//			}
//			if (e2 < dx) {
//				err += dx;
//				ny1 += sy;
//			}
//		}
//	}
}

// Function that returs the distance between the player's position and the ray's end point
double	distance_player_ray_end(int p_x, int p_y, int r_x, int r_y)
{
	return (sqrt((r_x - p_x) * (r_x - p_x) + (r_y - p_y) * (r_y - p_y)));
}

int almost_equal(double a, double b, double epsilon)
{
	return (fabs(a - b) < epsilon);
}

void	draw_rays(t_game *game, t_map *map, t_player *player, t_ray *ray)
{
	int	r, dof, mx, my, mp;
	double distT;
	int color;

//	int map_h[]=           //the map array. Edit to change level but keep the outer walls
//	{
//	 1,1,1,1,1,1,1,1,
//	 1,0,1,0,0,0,0,1,
//	 1,0,1,0,0,0,0,1,
//	 1,0,1,0,0,0,0,1,
//	 1,0,0,0,0,0,0,1,
//	 1,0,0,0,0,1,0,1,
//	 1,0,0,0,0,0,0,1,
//	 1,1,1,1,1,1,1,1,	
//	};
	// initialize ray angle DEGREE degrees back from the player angle
	ray->r_a = player->p_a - DEGREE * 30;
	// then we need to add the limits to the next angle bcs unit circle
	if (ray->r_a < 0)
		ray->r_a += 2 * M_PI;
	if (ray->r_a >= 2 * M_PI)
		ray->r_a -= 2 * M_PI;
	// how many rays will be drawn
	for (r = 0; r < 60; r++)
	{
		// HORIZONTAL
		// check horizontal lines - where the ray will first hit the closest horizontal line
		dof = 0;
		double distH = 1000000;
		int	hx = player->p_x;
		int	hy = player->p_y;
		double aTan = -1 / tan(ray->r_a);
		if (ray->r_a > M_PI) // ray looking up - determined from the ray angle
		{
			ray->r_y = (((int)player->p_y >> 6) << 6) - 0.0001;
			ray->r_x = (player->p_y - ray->r_y) * aTan + player->p_x;
			// once we have first ray hit position, we need next x and y offset
			ray->y_offset = (-TILE_SIZE);
			ray->x_offset = (-ray->y_offset) * aTan;
		}
		if (ray->r_a < M_PI) // ray looking down - determined from the ray angle
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
			dof = 8;
		}
	//	if (ray->r_a == 0 || ray->r_a == M_PI) // if the ray is looking straight left or right, it will never hit a horizontal line
	//	{
	//		ray->r_x = player->p_x;
	//		ray->r_y = player->p_y;
	//		dof = 8;
	//	}
		while (dof < 8)
		{
			mx = (int)(ray->r_x) >> 6;
			my = (int)(ray->r_y) >> 6;
			mp = my * map->map_width + mx;
		//	printf("mx: %d\n", mx);
		//	printf("my: %d\n", my);
		//	printf("mp: %d\n", mp);
			if (mx >= 0 && mx < map->map_width && my >= 0 && my < map->map_height && map->grid[my][mx] == '1') // hit wall
			{
				hx = ray->r_x;
				hy = ray->r_y;
				distH = distance_player_ray_end(player->p_x, player->p_y, hx, hy);
				dof = 8;
			}
			else
			{
				ray->r_x += ray->x_offset;
				ray->r_y += ray->y_offset;
				dof += 1;
			}
		}
	//	printf("r_y: %d %d\n", ray->r_y, ray->r_y >> 6);
	//	printf("r_x: %d %d\n", ray->r_x, ray->r_x >> 6);
	//	draw_line(player->p_x, player->p_y, ray->r_x, ray->r_y, 0x00FF00FF, game->image);
		
		// VERTICAL
		// check vertical lines - where the ray will first hit the closest vertical line
		dof = 0;
		double distV = 1000000;
		int	vx = player->p_x;
		int	vy = player->p_y;
		double nTan = (-tan(ray->r_a));
		if (ray->r_a > (M_PI / 2) && ray->r_a < (3 * M_PI / 2)) // ray looking left - determined from the ray angle
		{
			ray->r_x = (((int)player->p_x >> 6) << 6) - 0.0001;
			ray->r_y = (player->p_x - ray->r_x) * nTan + player->p_y;
			// once we have first ray hit position, we need next x and y offset
			ray->x_offset = (-TILE_SIZE);
			ray->y_offset = (-ray->x_offset) * nTan;
		}
		if (ray->r_a < (M_PI / 2) || ray->r_a > (3 * M_PI / 2)) // ray looking right - determined from the ray angle
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
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(ray->r_x) >> 6;
			my = (int)(ray->r_y) >> 6;
			mp = my * map->map_width + mx;
		//	printf("mx: %d\n", mx);
		//	printf("my: %d\n", my);
		//	printf("mp: %d\n", mp);
			if (mx >= 0 && mx < map->map_width && my >= 0 && my < map->map_height && map->grid[my][mx] == '1') // hit wall
			{
				vx = ray->r_x;
				vy = ray->r_y;
				distV = distance_player_ray_end(player->p_x, player->p_y, vx, vy);
				dof = 8;
			}
			else
			{
				ray->r_x += ray->x_offset;
				ray->r_y += ray->y_offset;
				dof += 1;
			}
		}
	//	printf("r_y: %d %d\n", ray->r_y, ray->r_y >> 6);
	//	printf("r_x: %d %d\n", ray->r_x, ray->r_x >> 6);
	// pick the shortest distance
		if (distV < distH)
		{
			ray->r_x = vx;
			ray->r_y = vy;
			distT = distV;
			color = 0xFF0000FF;
		}
		if (distH < distV)
		{
			ray->r_x = hx;
			ray->r_y = hy;
			distT = distH;
			color = 0x913831FF;
		}
		draw_line(player->p_x, player->p_y, ray->r_x, ray->r_y, 0xFF0000FF, game->image);
		// 3D WALLS
		// distance between the player angle and the ray angle
		double ca = player->p_a - ray->r_a;
		if (ca < 0)
			ca += 2 * M_PI;
		if (ca >= 2 * M_PI)
			ca -= 2 * M_PI;
		// multiply the ray distance by the cosine of that ray angle
		distT = distT * cos(ca); // fix fish eye
		double lineH = (TILE_SIZE * 320) / distT; // line height
		if (lineH > 320)
			lineH = 320;
		double lineO = 160 - lineH / 2; // line offset
		draw_line_thickness(r * map->map_width + 530, lineO, r * map->map_height + 530, lineH + lineO, color, 5, game->image);
		// NEXT RAY setup
		// if drawing more lines, the angle need to more after each line
		ray->r_a += DEGREE;
		// and the limits need to be set again bcs unit circle
		if (ray->r_a < 0)
			ray->r_a += 2 * M_PI;
		if (ray->r_a >= 2 * M_PI)
			ray->r_a -= 2 * M_PI;
	}
}

void	draw(void *param)
{
	t_game	*game;
    t_player    *player;
	int		x;
	int		y;
	int		player_flag;
    int     i;
    int     j;

	game = (t_game *) param;
    player = game->player;
	player_flag = 0;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
    		mlx_put_pixel(game->image, x, y, 0x00000000); // black
			y++;
		}
		x++;
	}
    // Draw map grid
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
	// Draw lines in map grid
	// vertical
	y = 0;
	x = TILE_SIZE;
	for (int i = 1; i < game->map->map_height; i++)
	{
			draw_line(x, y, x, y + (TILE_SIZE * game->map->map_height), 0x000000FF, game->image); // black
			x += TILE_SIZE;
	}
	// horizontal
	y = TILE_SIZE;
	x = 0;
	for (int i = 1; i < game->map->map_width; i++)
	{
			draw_line(x, y, x + (TILE_SIZE * game->map->map_width), y, 0x000000FF, game->image); // black
			y += TILE_SIZE;
	}
	// Draw rays
	draw_rays(game, game->map, game->player, game->ray);
	// Draw player
	draw_square(game->image, game->player->p_x, game->player->p_y, PLAYER_SIZE, 0xFFFF00FF); // yellow
    // Draw a line to where the player is looking
	draw_line_thickness(player->p_x, player->p_y, player->p_x + player->p_dx * 5,
		player->p_y + player->p_dy * 5, 0xFFFF00FF, 3, game->image);
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

