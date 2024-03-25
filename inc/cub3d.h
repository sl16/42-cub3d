/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:17:09 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/25 17:16:19 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERR_MALLOC_GAME	"Couldn't allocate memory for struct 'game'."
# define ERR_MALLOC_MAP		"Couldn't allocate memory for struct 'map'."
# define ERR_ARGC			"Provide a path to your desired map only."
# define ERR_ARGV			"Provide a .cub file."
# define ERR_OPEN			"File cannot be opened."
# define ERR_TXT_OPEN		"A texture file cannot be opened."
# define ERR_DUP_VALUE		"The file contains duplicate value identifiers."
# define ERR_MISSING_VALUE	"The provided map is missing a required value."
# define ERR_COLOR			"Provided RGB colors must be set in 0-255 range."
# define ERR_COLOR_INTMAX	"Provided RGB colors cause INTMAX overflow."
# define ERR_MAP_NOT_FOUND	"No valid map found in provided file."
# define ERR_MAP_NOT_CLOSED	"The map's perimeter is not enclosed in walls."
# define ERR_MAP_EMPTY_LINE	"The map must not contain empty lines."
# define ERR_MAP_CORNERS	"The map's corners are not fully enclosed in walls."
# define ERR_MAP_CH_INVALID	"The map contains invalid characters."
# define ERR_MAP_START		"The map must contain precisely one starting point."
# define ERR_MAP_ADJACENT	"The map's inner spaces must be enclosed."
# define ERR_MAP_CORNER		"The map's corners must be enclosed."

# define WIDTH 1280
# define HEIGHT 768
# define TILE_SIZE 32
# define TILE_SIZE_2D 16
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 5
# define PLAYER_SIZE 6
# define MINIMAP_ZOOM 5

# define COLOR_FREE_SPACE_2D 0x703023FF
# define COLOR_WALL_2D 0xFFEEDCFF
# define COLOR_OUTSIDE_2D 0x5B5B5BFF
# define COLOR_PLAYER 0xFFDB58FF

# include "../libftprintf/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include <X11/Xlib.h>

typedef union u_clr
{
	unsigned int	rgba;
	struct
	{
		unsigned char	a;
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
	};
}				t_clr;

typedef struct s_map
{
	int				fd;
	char			**parsed_file;
	char			**grid;
	int				map_width;
	int				map_height;
	int				start_count;
	int				start_x;
	int				start_y;
	char			start_dir;
	char			*txt_no;
	char			*txt_so;
	char			*txt_we;
	char			*txt_ea;
	mlx_texture_t	*mlx_txt_no;
	mlx_texture_t	*mlx_txt_so;
	mlx_texture_t	*mlx_txt_we;
	mlx_texture_t	*mlx_txt_ea;
	t_clr			clr_floor;
	t_clr			clr_ceiling;
}				t_map;

typedef struct s_player
{
	int		p_x;
	int		p_y;
	int		mini_p_x;
	int		mini_p_y;
	double	p_a; // player angle
	double	fov_rd; // field of view in radians
	double	move_y;
	double	move_x;
}	t_player;

typedef struct s_ray
{
	int			ray_counter;
	double		r_a; // ray angle
	double		r_x;
	double		r_y;
	double		angle_nor; // normalized ray angle
	double		angle_diff;
	int			angle_orientation;
	double		vy; // vertical ray hit
	double		vx; // vertical ray hit
	double		dist_ver; // vertical ray hit
	double		hy;	// horizontal ray hit
	double		hx;	// horizontal ray hit
	double		dist_hor;	// horizontal ray hit
	double		dist_total; // distance to the wall
	double		y_step;
	double		x_step;
	int			pixel;
	uint32_t	color;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*animation;
	mlx_texture_t	*animation_txt;
	t_map			*map;
	t_player		*player;
	t_ray			*ray;
}	t_game;

typedef struct s_wall
{
	double	wall_start;
	double	wall_end;
	double	wall_height;
}	t_wall;

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

// TEMPORARY
void	load_textures(t_map *map);

// init.c
bool	init_mlx42(t_game *game);
void	init_game_struct(t_game *game);
int		init_empty_struct(t_game *game);
void	init_empty_textures(t_game *game);

// rays.c
void	cast_rays_3d(t_game *game, t_player *player, t_ray *ray);
double	normalize_angle(double angle);

// rays_calculate.c
void	calculate_vertical_hit(t_map *map, t_player *player, t_ray *ray);
void	calculate_horizontal_hit(t_map *map, t_player *player, t_ray *ray);

// draw_2d.c
void	draw_2d_minimap(t_game *game, t_player *player);

// draw_3d.c
void	project_ray_into_3d(t_game *game, int ray_counter);

// draw_utils.c
void	draw_square(mlx_image_t *image, t_draw_info *draw_info);
void	draw_line(mlx_image_t *image, t_draw_info *draw_info);
void	print_grid(char **grid, int map_height);

// keys.c
void	handle_key_actions(void *param);

// error.c
int		error_print(const char *error_message);
void	error_print_exit(char *error_message, t_game *game);

// free.c
int		free_game_parser(t_game *game);
void	free_game_full(t_game *game);
int		free_map(t_map *map);
int		free_str_arr(char **arr);

// checker_arg.c
int		checker_arg(int argc, char **argv, t_game *game);

// checker_map.c
void	checker_map(t_map *map, t_game *game);

// checker_duplicates.c
void	checker_duplicates(t_game *game);

// parser_file.c, parser_values.c, parser_utils.c, parser_utils2.c
int		parser(t_game *game);
char	*value_parser(char *value, char **parsed_file);
void	clr_parser(char *value, char **parsed_file, t_game *game);
int		clr_atoi(const char *nptr, int *intmax_check);
void	load_and_verify_textures(t_game *game);
int		is_space(char input);
int		is_wall(char input);
int		line_has_spaces_only(char *line);
int		increment_if_space(char *input, int i);
int		find_last_char(char *input);
void	get_map_dimensions(t_map *map);
void	copy_map(t_map *map, t_game *game);
void	convert_spaces_to_walls(t_map *map);
void	check_top_spaces(int x, int y, t_map *map, t_game *game);
void	check_bot_spaces(int x, int y, t_map *map, t_game *game);

// debug.c
int		print_map(char **map);
int		print_values(t_game *game);

// animation.c
void	play_animation(t_game *game);

#endif
