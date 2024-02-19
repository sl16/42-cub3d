#ifndef CUB3D_H
# define CUB3D_H

# define ERR_MALLOC_GAME	"Couldn't allocate memory for struct 'game'."
# define ERR_MALLOC_MAP		"Couldn't allocate memory for struct 'map'."
# define ERR_ARGC			"Provide a path to your desired map only."
# define ERR_ARGV			"Provide a .cub file."
# define ERR_OPEN			"File cannot be opened."
# define WIDTH 1200
# define HEIGHT 800
# define TILE_SIZE 30
# define FOV 60
# define PLAYER_SPEED 4
# define ROTATION_SPEED 0.045

# include "../libftprintf/ft_printf.h"

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <../MLX42/include/MLX42/MLX42.h>

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
	double	ray_ngl; // ray angle
	double	distance; // disntance to the wall
	int		flag; // flag for the wall
}	t_ray;

typedef struct	player
{
	int		p_x;
	int		p_y;
	double	p_angle;
	float	fov;
	int  rot; // rotation flag
	int  l_r; // left right flag
	int  u_d; // up down flag
}	t_player;

typedef struct s_game
{
	mlx_t       *mlx;
	mlx_image_t	*image;
	t_map	    *map;
	t_ray		*ray;
	t_player	*player;
}				t_game;

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


#endif
