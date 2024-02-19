#include "./inc/cub3d.h"

int	init_game_struct(t_game *game)
{
	game->map = calloc(1, sizeof(t_map));
	game->map->grid = calloc(10, sizeof(char *)); // init the map
	game->map->grid[0] = ft_strdup("1111111111111111111111111"); //fill the map
	game->map->grid[1] = ft_strdup("1000000000000000000100001");
	game->map->grid[2] = ft_strdup("1001000000000P00000000001");
	game->map->grid[3] = ft_strdup("1001000000000000001000001");
	game->map->grid[4] = ft_strdup("1001000000000000001000001");
	game->map->grid[5] = ft_strdup("1001000000100000001000001");
	game->map->grid[6] = ft_strdup("1001000000000000001000001");
	game->map->grid[7] = ft_strdup("1001000000001000001000001");
	game->map->grid[8] = ft_strdup("1111111111111111111111111");
	game->map->grid[9] = NULL;
	game->map->p_y = 3;
	game->map->p_x = 14;
	game->map->map_width = 25;
	game->map->map_height = 9;
	// Init player
	game->player = calloc(1, sizeof(t_player));
	game->player->p_x = game->map->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	game->player->p_y = game->map->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	game->player->fov = (FOV * M_PI) / 180.0; // field of view in radians
	game->player->p_angle = M_PI; // player angle

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
	mlx_delete_image(game->mlx, game->image);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
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

// check the unit circle
int unit_circle(float angle, char point) 
{
	if (point == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (point == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

// check the intersection
int inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

// check the wall hit
int wall_hit(float x, float y, t_game *game) 
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= game->map->map_height || x_m >= game->map->map_width))
		return (0);
	if (game->map->grid[y_m] && x_m <= (int) ft_strlen(game->map->grid[y_m]))
		if (game->map->grid[y_m][x_m] == '1')
			return (0);
	return (1);
}

float get_h_inter(t_game *game, float angl) // get the horizontal intersection
{
 float h_x;
 float h_y;
 float x_step;
 float y_step;
 int  pixel;

 y_step = TILE_SIZE;
 x_step = TILE_SIZE / tan(angl);
 h_y = floor(game->player->p_y / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angl, &h_y, &y_step, 1);
 h_x = game->player->p_x + (h_y - game->player->p_y) / tan(angl);
 if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
  x_step *= -1;
 while (wall_hit(h_x, h_y - pixel, game)) // check the wall hit whit the pixel value
 {
  h_x += x_step;
  h_y += y_step;
 }
 return (sqrt(pow(h_x - game->player->p_x, 2) + pow(h_y - game->player->p_y, 2))); // get the distance
}

float get_v_inter(t_game *game, float angle) // get the vertical intersection
{
 float v_x;
 float v_y;
 float x_step;
 float y_step;
 int  pixel;

 x_step = TILE_SIZE; 
 y_step = TILE_SIZE * tan(angle);
 v_x = floor(game->player->p_x / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angle, &v_x, &x_step, 0); // check the intersection and get the pixel value
 v_y = game->player->p_y + (v_x - game->player->p_x) * tan(angle);
 if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0)) // check y_step value
  y_step *= -1;
 while (wall_hit(v_x - pixel, v_y, game)) // check the wall hit whit the pixel value
 {
  v_x += x_step;
  v_y += y_step;
 }
 return (sqrt(pow(v_x - game->player->p_x, 2) + pow(v_y - game->player->p_y, 2))); // get the distance
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color) // put the pixel
{
 if (x < 0) // check the x position
  return ;
 else if (x >= WIDTH)
  return ;
 if (y < 0) // check the y position
  return ;
 else if (y >= HEIGHT)
  return ;
 mlx_put_pixel(game->image, x, y, color); // put the pixel
}

float nor_angle(float angle) // normalize the angle
{
 if (angle < 0)
  angle += (2 * M_PI);
 if (angle > (2 * M_PI))
  angle -= (2 * M_PI);
 return (angle);
}

void draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
 int  i;

 i = b_pix;
 while (i < HEIGHT)
  my_mlx_pixel_put(game, ray, i++, 0xB99470FF); // floor
 i = 0;
 while (i < t_pix)
  my_mlx_pixel_put(game, ray, i++, 0x89CFF3FF); // ceiling
}

int get_color(t_game *game, int flag) // get the color of the wall
{
 game->ray->ray_ngl = nor_angle(game->ray->ray_ngl); // normalize the angle
 if (flag == 0)
 {
  if (game->ray->ray_ngl > M_PI / 2 && game->ray->ray_ngl < 3 * (M_PI / 2))
   return (0xB5B5B5FF); // west wall
  else
   return (0xB5B5B5FF); // east wall
 }
 else
 {
  if (game->ray->ray_ngl > 0 && game->ray->ray_ngl < M_PI)
   return (0xF5F5F5FF); // south wall
  else
   return (0xF5F5F5FF); // north wall
 }
}

void draw_wall(t_game *game, int ray, int t_pix, int b_pix) // draw the wall
{
 int color;

 color = get_color(game, game->ray->flag);
 while (t_pix < b_pix)
  my_mlx_pixel_put(game, ray, t_pix++, color);
}

void render_wall(t_game *game, int ray) // render the wall
{
 double wall_h;
 double b_pix;
 double t_pix;

 game->ray->distance *= cos(nor_angle(game->ray->ray_ngl - game->player->p_angle)); // fix the fisheye
 wall_h = (TILE_SIZE / game->ray->distance) * ((WIDTH / 2) / tan(game->player->fov / 2)); // get the wall height
 b_pix = (WIDTH / 2) + (wall_h / 2); // get the bottom pixel
 t_pix = (WIDTH / 2) - (wall_h / 2); // get the top pixel
 if (b_pix > HEIGHT) // check the bottom pixel
  b_pix = HEIGHT;
 if (t_pix < 0) // check the top pixel
  t_pix = 0;
 draw_wall(game, ray, t_pix, b_pix); // draw the wall
 draw_floor_ceiling(game, ray, t_pix, b_pix); // draw the floor and the ceiling
}

void cast_rays(t_game *game) // cast the rays
{
 double h_inter;
 double v_inter;
 int  ray;

 ray = 0;
 game->ray->ray_ngl = game->player->p_angle - (game->player->fov / 2); // the start angle
 while (ray < WIDTH) // loop for the rays
 {
  game->ray->flag = 0; // flag for the wall
  h_inter = get_h_inter(game, nor_angle(game->ray->ray_ngl)); // get the horizontal intersection
  v_inter = get_v_inter(game, nor_angle(game->ray->ray_ngl)); // get the vertical intersection
  if (v_inter <= h_inter) // check the distance
   game->ray->distance = v_inter; // get the distance
  else
  {
  	game->ray->distance = h_inter; // get the distance
  	game->ray->flag = 1; // flag for the wall
  }
  render_wall(game, ray); // render the wall
  ray++; // next ray
  game->ray->ray_ngl += (game->player->fov / WIDTH); // next angle
 }
}

void ft_reles(mlx_key_data_t keydata, t_game *game) // release the key
{
 if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
  game->player->l_r = 0;
 else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
  game->player->l_r = 0;
 else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
  game->player->u_d = 0;
 else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
  game->player->u_d = 0;
 else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
  game->player->rot = 0;
 else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
  game->player->rot = 0;
}

void mlx_key(mlx_key_data_t keydata, void *param) // key press
{
 t_game *game;

 game = param;
 if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
 {
	free_game_struct(game);
	exit(0);
 }
 else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
  game->player->l_r = -1;
 else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
  game->player->l_r = 1;
 else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
  game->player->u_d = -1;
 else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
  game->player->u_d = 1;
 else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
  game->player->rot = -1;
 else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
  game->player->rot = 1;
 ft_reles(keydata, game); // release the key
}

void rotate_player(t_game *game, int i) // rotate the player
{
 if (i == 1)
 {
  game->player->p_angle += ROTATION_SPEED; // rotate right
  if (game->player->p_angle > 2 * M_PI)
   game->player->p_angle -= 2 * M_PI;
 }
 else
 {
  game->player->p_angle -= ROTATION_SPEED; // rotate left
  if (game->player->p_angle < 0)
   game->player->p_angle += 2 * M_PI;
 }
}

void move_player(t_game *game, double move_x, double move_y) // move the player
{
 int  map_grid_y;
 int  map_grid_x;
 int  new_x;
 int  new_y;

 new_x = roundf(game->player->p_x + move_x); // get the new x position
 new_y = roundf(game->player->p_y + move_y); // get the new y position
 map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
 map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
 if (game->map->grid[map_grid_y][map_grid_x] != '1' && \
 (game->map->grid[map_grid_y][game->player->p_x / TILE_SIZE] != '1' && \
 game->map->grid[game->player->p_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
 {
  game->player->p_x = new_x; // move the player
  game->player->p_y = new_y; // move the player
 }
}

void hook(t_game *game, double move_x, double move_y) // hook the player
{
 if (game->player->rot == 1) //rotate right
  rotate_player(game, 1);
 if (game->player->rot == -1) //rotate left
  rotate_player(game, 0);
 if (game->player->l_r == 1) //move right
 {
  move_x = -sin(game->player->p_angle) * PLAYER_SPEED;
  move_y = cos(game->player->p_angle) * PLAYER_SPEED;
 }
 if (game->player->l_r == -1) //move left
 {
  move_x = sin(game->player->p_angle) * PLAYER_SPEED;
  move_y = -cos(game->player->p_angle) * PLAYER_SPEED;
 }
 if (game->player->u_d == 1) //move up
 {
  move_x = cos(game->player->p_angle) * PLAYER_SPEED;
  move_y = sin(game->player->p_angle) * PLAYER_SPEED;
 }
 if (game->player->u_d == -1) //move down
 {
  move_x = -cos(game->player->p_angle) * PLAYER_SPEED;
  move_y = -sin(game->player->p_angle) * PLAYER_SPEED;
 }
 move_player(game, move_x, move_y); // move the player
}

void	draw_game(void *param)
{
	t_game *game;

	game = param;
	mlx_delete_image(game->mlx, game->image);
	if (!(game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		exit(1);
	}
 	hook(game, 0, 0); // hook the player
	cast_rays(game);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		exit(1);
	}
} 

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_game	game;

	// Init struct
	init_game_struct(&game);
	print_grid(game.map->grid, game.map->map_height);
	// Init mlx
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 1)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Start game
	mlx_loop_hook(game.mlx, &draw_game, &game);
	mlx_key_hook(game.mlx, &mlx_key, &game);
	mlx_loop(game.mlx);
	free_game_struct(&game);
	return (EXIT_SUCCESS);
}
