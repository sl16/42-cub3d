#ifndef CUB3D_H
# define CUB3D_H

# define ERR_MALLOC_GAME	"Couldn't allocate memory for struct 'game'."
# define ERR_MALLOC_MAP		"Couldn't allocate memory for struct 'map'."
# define ERR_ARGC			"Provide a path to your desired map only."
# define ERR_ARGV			"Provide a .cub file."
# define ERR_OPEN			"File cannot be opened."
# define WIDTH 1280
# define HEIGHT 780
# define TILE_SIZE 32
# define TILE_SIZE_2D 32
# define MINI_MAP 2
# define FOV 60
# define PLAYER_SPEED 4
# define ROTATION_SPEED 0.04
# define PLAYER_SIZE 8
# define PRECISION 0.000001
# define DOF 100

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include "../libftprintf/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"

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
}				t_map;

typedef struct s_ray
{
	double	r_x;
	double	r_y;
	double	r_a; // ray angle
	double	y_offset;
	double	x_offset;
	int		color;
}	t_ray;

typedef struct s_player
{
	double	p_x;
	double	p_y;
	double	p_dx; // delta x
	double	p_dy; // delta y
	double	p_a; // player angle
	double	fov_rd;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_map		*map;
	t_ray		*ray;
	t_player	*player;
	double		degree;
}				t_game;

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

typedef struct s_ray_calculation
{
	int		mx;
	int		my;
	int		dof;
	double	hx;
	double	hy;
	double	tan_pos;
	double	vx;
	double	vy;
	double	tan_neg;
	double	dist_hor;
	double	dist_ver;
	double	dist_total;
	double	angle_diff;
	double	line_height;
	double	line_offset;
	double	angle_nor;
}	t_ray_calculation;

int		error_print(char *error_message);
void	error_print_exit(char *error_message, t_game *game);

int		free_game(t_game *game);
int		free_map(t_map *map);
int		free_str_arr(char **arr);

int		init_empty_struct(t_game *game);
int		arg_checker(int argc, char **argv, t_game *game);

int		map_parser(t_game *game);
int		print_map(char **map);
int		print_values(t_game *game);

// init.c
int		init_game_struct(t_game *game);
int		init_mlx42(t_game *game);

// precision.c
bool	almost_equal(double a, double b, double epsilon);
bool	almost_less_than(double a, double b, double epsilon);
bool	almost_greater_than(double a, double b, double epsilon);

// rays.c
void	draw_rays(t_game *game, t_map *map, t_player *player, t_ray *ray);

// draw.c
void	draw_line(mlx_image_t *image, t_draw_info draw_info);
void	draw_line_thickness(mlx_image_t *image, t_draw_info draw_info);
void	draw_square(mlx_image_t *image, t_draw_info draw_info);
void	draw_map_grid(t_game *game);
void	draw_lines_in_map_grid(t_game *game);
void	print_grid(char **grid, int map_height);

// keys.c
void	handle_key_actions(void *param);

// free.c
void	free_game_struct(t_game *game);

#endif
