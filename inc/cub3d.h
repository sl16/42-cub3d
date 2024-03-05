#ifndef CUB3D_H
# define CUB3D_H

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
	int		p_x;
	int		p_y;
	double	p_a; // player angle
	double	fov_rd; // field of view in radians
}	t_player;

typedef struct s_ray
{
	double	r_a; // ray angle
	double	r_x;
	double	r_y;
	double	angle_nor; // normalized ray angle
	double	angle_diff;
	double	vy;
	double	vx;
	double	dist_ver;
	double	hy;
	double	hx;
	double	dist_hor;
	double	dist_total; // distance to the wall
	double	y_step;
	double	x_step;
	int		pixel;
	int		color;
}	t_ray;

typedef struct s_map
{
	int		fd;
	char	**parsed_file;
	char	**grid;
	int		texture_width;
	int		texture_height;
	int		map_width;
	int		map_height;
	int		start_x;
	int		start_y;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_ray		*ray;
	t_map		*map;
	t_player	*player;
}	t_game;

typedef struct s_draw_info
{
	double		y1;
	double		x1;
	double		y2;
	double		x2;
	uint32_t	color;
	int			size;
}	t_draw_info;

typedef struct s_draw_delta
{
	int		length;
	double	delta_x;
	double	delta_y;
}	t_draw_delta;

typedef enum s_orientation
{
	HORIZONTAL,
	VERTICAL
}	t_orientation;

// one_file

void	cast_rays_3d(t_game *game, t_player *player, t_ray *ray);
void	cast_rays_2d(t_game *game, t_player *player, t_ray *ray);
double	normalize_angle(double angle);

// init.c
bool	init_mlx42(t_game *game);
void	init_game_struct(t_game *game);

// draw_2d.c
void	draw_2d_map_grid(t_game *game);
void	draw_2d_rays(mlx_image_t *image, t_player *player, t_ray *ray);
void	draw_2d_player(mlx_image_t *image, t_player *player);

// draw_3d.c
void	draw_3d_game(t_game *game, int ray_counter);

// draw_utils.c
void	draw_square(mlx_image_t *image, t_draw_info draw_info);
void	draw_line(mlx_image_t *image, t_draw_info draw_info);
void	print_grid(char **grid, int map_height);

// keys.c
void	handle_key_actions(void *param);

// free.c
void	free_game_struct(t_game *game);

#endif
