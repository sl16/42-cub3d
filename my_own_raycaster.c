/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_own_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:48:33 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/20 19:16:10 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

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
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) // move left
		player->p_x -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)) // move up
	{
		//player->p_y -= 5;
        player->p_x += player->p_dx; 
        player->p_y += player->p_dy; 
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) // move right
		player->p_x += 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)) // move down
	{
		//player->p_y += 5;
        player->p_x -= player->p_dx; 
        player->p_y -= player->p_dy; 
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        player->p_a -= 0.1;
        if (player->p_a < 0)
            player->p_a += 2 * M_PI;
        player->p_dx = cos(player->p_a) * 5;
        player->p_dy = sin(player->p_a) * 5;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        player->p_a += 0.1;
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

void	draw_square(mlx_image_t *image, float p_x, float p_y, int size, int color)
{
	int		x;
	int		y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
   			mlx_put_pixel(image, (p_x - size / 2) + x,
				(p_y - size / 2) + y, color); // yellow
			y++;
		}
		x++;
	}
}

void	draw_line(int x1, int y1, int x2, int y2, int color, mlx_image_t *image)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (1) {
		mlx_put_pixel(image, x1, y1, color); // yellow
		if (x1 == x2 && y1 == y2) {
			break;
		}
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
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
    		x += TILE_SIZE + 1;
    		j++;
    	}
    	y += TILE_SIZE + 1;
        i++;
    }
	// Draw player
	draw_square(game->image, game->player->p_x, game->player->p_y, PLAYER_SIZE, 0xFFFF00FF); // yellow
    // Draw a line to where the player is looking
	draw_line(player->p_x, player->p_y, player->p_x + player->p_dx * 5,
		player->p_y + player->p_dy * 5, 0xFFFF00FF, game->image);
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

