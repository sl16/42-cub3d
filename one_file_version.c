# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include "../libftprintf/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 768
# define TILE_SIZE 32
# define TILE_SIZE_2D 16
# define MINI_MAP 2
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 5
# define PLAYER_SIZE 8
# define PRECISION 0.000001

typedef struct s_player
{
 int	p_x;
 int	p_y;
 double	p_a; // player angle
 double	fov_rd; // field of view in radians
} t_player;

typedef struct s_ray
{
 double	r_a; // ray angle
 double	angle_nor; // normalized ray angle
 double	vy;
 double	vx;
 double dist_ver;
 double	hy;
 double	hx;
 double dist_hor;
 double dist_total; // distance to the wall
 int	color;
} t_ray;

typedef struct s_map
{
	int		fd;
	char	**parsed_file;
	char	**grid;
	char	*texture_NO;
	char	*texture_SO;
	char	*texture_WE;
	char	*texture_EA;
	int		texture_width;
	int		texture_height;
	int		color_floor;
	int		color_ceiling;
	int		map_width;
	int		map_height;
	int		p_x;
	int		p_y;
}	t_map;

typedef struct s_game
{
 mlx_t			*mlx;
 mlx_image_t	*image;
 t_ray			*ray;
 t_map			*map;
 t_player		*player;
}	t_game;

typedef struct s_draw_info
{
	int			y1;
	int			x1;
	int			y2;
	int			x2;
	uint32_t	color;
	int			size;
}	t_draw_info;

typedef struct s_draw_delta
{
	int		length;
	double	delta_x;
	double	delta_y;
}	t_draw_delta;

void	free_game_struct(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->map_height)
	{
		if (game->map->grid[i])
			free(game->map->grid[i]);
		i++;
	}
	if (game->map->grid)
		free(game->map->grid);
	if (game->map)
		free(game->map);
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	mlx_delete_image(game->mlx, game->image);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
}

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

bool	almost_equal(double a, double b, double epsilon)
{
	return (fabs(a - b) < epsilon);
}

bool	almost_less_than(double a, double b, double epsilon)
{
	return (b - a > epsilon);
}

bool	almost_greater_than(double a, double b, double epsilon)
{
	return (a - b > epsilon);
}

double	normalize_angle(double angle)
{
	if (almost_less_than(angle, 0, PRECISION))
		angle += 2 * M_PI;
	if (almost_greater_than(angle, 2 * M_PI, PRECISION))
		angle -= 2 * M_PI;
	return (angle);
}

void draw_floor_ceiling(t_game *game, int ray, int start_pxl, int end_pxl)
{
 int  i;

 i = end_pxl;
 while (i < HEIGHT)
 {
  mlx_put_pixel(game->image, ray, i, 0xB99470FF); // floor
  i++;
 }
 i = 0;
 while (i < start_pxl)
 {
  mlx_put_pixel(game->image, ray, i, 0x89CFF3FF); // ceiling
  i++;
 }
}

void draw_wall(t_game *game, int ray, int start_pxl, int end_pxl)
{
 while (start_pxl < end_pxl)
 {
  mlx_put_pixel(game->image, ray, start_pxl, game->ray->color);
  start_pxl++;
 }
}

void render_wall(t_game *game, int ray)
{
 double wall_height;
 double start_pxl;
 double end_pxl;

 game->ray->dist_total *= cos(normalize_angle(game->ray->r_a - game->player->p_a)); // fix the fisheye
 wall_height = (TILE_SIZE / game->ray->dist_total) * ((WIDTH / 2) / tan(game->player->fov_rd / 2)); // get the wall height
 start_pxl = (HEIGHT / 2) + (wall_height / 2); // get the bottom pixel
 end_pxl = (HEIGHT / 2) - (wall_height / 2); // get the top pixel
 if (start_pxl > HEIGHT) // check the bottom pixel
  start_pxl = HEIGHT;
 if (end_pxl < 0) // check the top pixel
  end_pxl = 0;
 draw_wall(game, ray, end_pxl, start_pxl); // draw the wall
 draw_floor_ceiling(game, ray, end_pxl, start_pxl); // draw the floor and the ceiling
}

int unit_circle(double angle, char c)
{
 if (c == 'x')
 {
  if (angle > 0 && angle < M_PI)
   return (1);
 }
 else if (c == 'y')
 {
  if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
   return (1);
 }
 return (0);
}

int wall_hit(double x, double y, t_map *map)
{
 int  x_m;
 int  y_m;

 if (x < 0 || y < 0)
  return (0);
 x_m = floor (x / TILE_SIZE); // get the x position in the map
 y_m = floor (y / TILE_SIZE); // get the y position in the map
 if (y_m >= map->map_height || y_m < 0 || x_m >= map->map_width || x_m < 0)
  return (0);
 if (map->grid[y_m] && x_m <= (int)strlen(map->grid[y_m]))
  if (map->grid[y_m][x_m] == '1')
   return (0);
 return (1);
}

int inter_check(double angle, double *inter, double *step, int is_horizon)
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

double	distance_player_ray_end(double p_x, double p_y, double r_x, double r_y)
{
	return (sqrt((r_x - p_x) * (r_x - p_x) + (r_y - p_y) * (r_y - p_y)));
}

void calculate_vertical_hit(t_map *map, t_player *player, t_ray *ray, double angle)
{
 double	x_step;
 double	y_step;
 int	pixel;

 y_step = TILE_SIZE;
 x_step = TILE_SIZE / tan(angle);
 ray->hy = floor(player->p_y / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angle, &ray->hy, &y_step, 1);
 ray->hx = player->p_x + (ray->hy - player->p_y) / tan(angle);
 if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
  x_step *= -1;
 while (wall_hit(ray->hx, ray->hy - pixel, map))
 {
  ray->hx += x_step;
  ray->hy += y_step;
 }
 ray->dist_ver = distance_player_ray_end(player->p_x, player->p_y, ray->hx, ray->hy);
}

void calculate_horizontal_hit(t_map *map, t_player *player, t_ray *ray, double angle)
{
 double	x_step;
 double	y_step;
 int	pixel;

 x_step = TILE_SIZE; 
 y_step = TILE_SIZE * tan(angle);
 ray->vx = floor(player->p_x / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angle, &ray->vx, &x_step, 0);
 ray->vy = player->p_y + (ray->vx - player->p_x) * tan(angle);
 if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0))
  y_step *= -1;
 while (wall_hit(ray->vx - pixel, ray->vy, map))
 {
  ray->vx += x_step;
  ray->vy += y_step;
 }
 ray->dist_hor = distance_player_ray_end(player->p_x, player->p_y, ray->vx, ray->vy);
}

void	draw_2d_map_grid(t_game *game)
{
	int			i;
	int			j;
	t_draw_info	draw_info;

	i = 0;
	draw_info.y1 = TILE_SIZE_2D / 2;
	while (game->map->grid[i])
	{
		draw_info.x1 = TILE_SIZE_2D / 2;
		j = 0;
		while (game->map->grid[i][j])
		{
			draw_info.size = TILE_SIZE_2D;
			if (game->map->grid[i][j] == '1')
				draw_info.color = 0xFFFFFFFF;
			else if (game->map->grid[i][j] == '0')
				draw_info.color = 0xB99470FF;
			draw_square(game->image, draw_info);
			draw_info.x1 += TILE_SIZE_2D;
			j++;
		}
		draw_info.y1 += TILE_SIZE_2D;
		i++;
	}
}

void	draw_2d_rays(mlx_image_t *image, t_player *player, t_ray *ray)
{
	t_draw_info	draw_info;

	draw_info.y1 = player->p_y / MINI_MAP;
	draw_info.x1 = player->p_x / MINI_MAP;
	draw_info.y2 = (player->p_y + ray->dist_total * sin(ray->r_a)) / MINI_MAP;
	draw_info.x2 = (player->p_x + ray->dist_total * cos(ray->r_a)) / MINI_MAP;
	draw_info.color = ray->color;
	draw_line(image, draw_info);
}

void	draw_2d_player(mlx_image_t *image, t_player *player)
{
	t_draw_info	draw_info;

	draw_info.y1 = player->p_y / MINI_MAP;
	draw_info.x1 = player->p_x / MINI_MAP;
	draw_info.size = PLAYER_SIZE / MINI_MAP;
	draw_info.color = 0xFFFF00FF;
	draw_square(image, draw_info);
}

void	draw_2d_player_pov(mlx_image_t *image, t_player *player)
{
	t_draw_info	draw_info;

	draw_info.y1 = player->p_y / MINI_MAP;
	draw_info.x1 = player->p_x / MINI_MAP;
	draw_info.y2 = (player->p_y + 50 * sin(player->p_a)) / MINI_MAP;
	draw_info.x2 = (player->p_x + 50 * cos(player->p_a)) / MINI_MAP;
	draw_info.color = 0xFFFF00FF;
	draw_line(image, draw_info);
}

void	pick_shortest_ray(t_ray *ray)
{
	if (almost_less_than(ray->dist_hor, ray->dist_ver, PRECISION))
	{
		ray->dist_total = ray->dist_hor; // get the distance
		//ray->color = 0xFF0000FF;
 		if (almost_greater_than(ray->angle_nor, M_PI / 2, PRECISION) && almost_less_than(ray->angle_nor, 3 * (M_PI / 2), PRECISION))
 			ray->color = 0x0000FFFF; // south wall
 		else
 			ray->color = 0x913831FF; // north wall
	}
	else
	{
		ray->dist_total = ray->dist_ver; // get the distance
		//ray->color = 0x913831FF;
		if (almost_greater_than(ray->angle_nor, 0, PRECISION) && almost_less_than(ray->angle_nor, M_PI, PRECISION))
			ray->color = 0x00FF00FF; // east wall
		else
			ray->color = 0xB5B5B5FF; // west wall
	}
}

void cast_rays(t_game *game, t_player *player, t_ray *ray)
{
	int  ray_counter;
	
	ray->r_a = player->p_a - (player->fov_rd / 2);
	ray_counter = 0;
	while (ray_counter < WIDTH)
	{
		ray->angle_nor = normalize_angle(ray->r_a);
		calculate_vertical_hit(game->map, player, ray, ray->angle_nor);
		calculate_horizontal_hit(game->map, player, ray, ray->angle_nor);
		pick_shortest_ray(ray);
		render_wall(game, ray_counter);
		ray->r_a += (player->fov_rd / WIDTH);
		ray_counter++;
	}
	draw_2d_map_grid(game);
	draw_2d_player(game->image, player);
	ray->r_a = player->p_a - (player->fov_rd / 2);
	ray_counter = 0;
	while (ray_counter < WIDTH)
	{
		ray->angle_nor = normalize_angle(ray->r_a);
		calculate_vertical_hit(game->map, player, ray, ray->angle_nor);
		calculate_horizontal_hit(game->map, player, ray, ray->angle_nor);
		pick_shortest_ray(ray);
		draw_2d_rays(game->image, player, ray);
		ray->r_a += (player->fov_rd / WIDTH);
		ray_counter++;
	}
	draw_2d_player_pov(game->image, player);
}

void game_loop(void *param)
{
	t_game *game;

	game = (t_game *) param;
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		exit(EXIT_FAILURE);
	}
	cast_rays(game, game->player, game->ray);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		exit(EXIT_FAILURE);
	}
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

bool	init_mlx42(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!game->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		return (EXIT_FAILURE);
	}
	return (true);
}

static void	init_player(t_game *game)
{
	game->player = calloc(1, sizeof(t_player));
    game->player->p_x = game->map->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
    game->player->p_y = game->map->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
    game->player->p_a = M_PI;
    game->player->fov_rd = (FOV * M_PI) / 180; // field of view in radians
}

static void	init_ray(t_game *game)
{
	game->ray = calloc(1, sizeof(t_ray));
}

void	init_game_struct(t_game *game)
{
	game->map = calloc(1, sizeof(t_map));

//	game->map->grid = calloc(9, sizeof(char *));
//	game->map->grid[0] = ft_strdup("11111111");
//	game->map->grid[1] = ft_strdup("10100001");
//	game->map->grid[2] = ft_strdup("10100001");
//	game->map->grid[3] = ft_strdup("10100001");
//	game->map->grid[4] = ft_strdup("10000001");
//	game->map->grid[5] = ft_strdup("10P00101");
//	game->map->grid[6] = ft_strdup("10000001");
//	game->map->grid[7] = ft_strdup("11111111");
//	game->map->grid[8] = NULL;
//	game->map->map_width = 8;
//	game->map->map_height = 8;
//	game->map->p_y = 5;
//	game->map->p_x = 2;

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
	game->map->map_width = 25;
	game->map->map_height = 9;
	game->map->p_y = 3;
	game->map->p_x = 14;


//	game->map->grid = calloc(25, sizeof(char *));
//	game->map->grid[0] = ft_strdup("111111111111111111111111");
//	game->map->grid[1] = ft_strdup("100000000000000000000001");
//	game->map->grid[2] = ft_strdup("10000P000000000000000001");
//	game->map->grid[3] = ft_strdup("100000000000000000000001");
//	game->map->grid[4] = ft_strdup("100000111110000101010001");
//	game->map->grid[5] = ft_strdup("100000100010000000000001");
//	game->map->grid[6] = ft_strdup("100000100010000100010001");
//	game->map->grid[7] = ft_strdup("100000100010000000000001");
//	game->map->grid[8] = ft_strdup("100000110110000101010001");
//	game->map->grid[9] = ft_strdup("100000000000000000000001");
//	game->map->grid[10] = ft_strdup("100000000000000000000001");
//	game->map->grid[11] = ft_strdup("100000000000000000000001");
//	game->map->grid[12] = ft_strdup("100000000000000000000001");
//	game->map->grid[13] = ft_strdup("100000000000000000000001");
//	game->map->grid[14] = ft_strdup("100000000000000000000001");
//	game->map->grid[15] = ft_strdup("100000000000000000000001");
//	game->map->grid[16] = ft_strdup("111111111000000000000001");
//	game->map->grid[17] = ft_strdup("110100001000000000000001");
//	game->map->grid[18] = ft_strdup("110000101000000000000001");
//	game->map->grid[19] = ft_strdup("110100001000000000000001");
//	game->map->grid[20] = ft_strdup("110111111000000000000001");
//	game->map->grid[21] = ft_strdup("110000000000000000000001");
//	game->map->grid[22] = ft_strdup("111111111000000000000001");
//	game->map->grid[23] = ft_strdup("111111111111111111111111");
//	game->map->grid[24] = NULL;
//	game->map->map_width = 24;
//	game->map->map_height = 24;
//	game->map->p_y = 2;
//	game->map->p_x = 5;

	init_player(game);
	init_ray(game);
}

void	perform_move(t_map *map, t_player *player, double move_x, double move_y)
{
	int	new_p_x;
	int	new_p_y;
	int	grid_x;
	int	grid_y;

	new_p_x = roundf(player->p_x + move_x); // get the new x position
	new_p_y = roundf(player->p_y + move_y); // get the new y position
	grid_x = new_p_x / TILE_SIZE;
	grid_y = new_p_y / TILE_SIZE;
	if (grid_y >= 0 && grid_y < HEIGHT && grid_x >= 0 && grid_x < WIDTH) {
		if (map->grid[grid_y][grid_x] == '0') 
		{
			player->p_x = new_p_x;
			player->p_y = new_p_y;
		}
	}
}

void	handle_keys_move(t_game *game, t_map *map, t_player *player)
{
	double	move_x;
	double	move_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_x = cos(player->p_a) * PLAYER_SPEED;
		move_y = sin(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_x = -cos(player->p_a) * PLAYER_SPEED;
		move_y = -sin(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_x = -sin(player->p_a) * PLAYER_SPEED;
		move_y = cos(player->p_a) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_x = sin(player->p_a) * PLAYER_SPEED;
		move_y = -cos(player->p_a) * PLAYER_SPEED;
	}
	perform_move(map, player, move_x, move_y);
}

void	handle_keys_rotation(t_game *game, t_player *player)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		player->p_a -= ROTATION_SPEED;
		if (almost_less_than(player->p_a, 0, PRECISION))
			player->p_a += 2 * M_PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		player->p_a += ROTATION_SPEED;
		if (almost_greater_than(player->p_a, (2 * M_PI), PRECISION))
			player->p_a -= 2 * M_PI;
	}
}

void	handle_key_actions(void *param)
{
	t_game		*game;
	t_player	*player;
	t_map		*map;

	game = (t_game *) param;
	player = game->player;
	map = game->map;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_game_struct(game);
		exit(0);
	}
	handle_keys_move(game, map, player);
	handle_keys_rotation(game, player);
}

int main(void)
{
    t_game   game;

	init_game_struct(&game);
	print_grid(game.map->grid, game.map->map_height);
	if (!init_mlx42(&game))
        return (EXIT_FAILURE);
    mlx_loop_hook(game.mlx, &game_loop, &game); // game loop
    mlx_loop_hook(game.mlx, &handle_key_actions, &game); // key press and release
    mlx_loop(game.mlx); 
	free_game_struct(&game);
	mlx_terminate(game.mlx);
    return (EXIT_SUCCESS);
}