#ifndef CUB3D_H
# define CUB3D_H

# define ERR_MALLOC_GAME	"Couldn't allocate memory for struct 'game'."
# define ERR_MALLOC_MAP		"Couldn't allocate memory for struct 'map'."
# define ERR_ARGC			"Provide a path to your desired map only."
# define ERR_ARGV			"Provide a .cub file."
# define ERR_OPEN			"File cannot be opened."
# define ERR_MISSING_VALUE	"The provided map is missing a required value."
# define ERR_MAP_NOT_FOUND	"No valid map found in provided file."
# define ERR_MAP_NOT_CLOSED	"The map's perimeter is not enclosed in walls."

# include "../libftprintf/ft_printf.h"
# include "../minilibx_linux/mlx.h"

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/Xlib.h>

typedef union u_clr
{
	unsigned int	rgba;
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	a;
	};
}				t_clr;

typedef struct s_map
{
	int		fd;
	char	**parsed_file;
	char	**map;
	int		width;
	int		height;

	char	*txt_NO;
	char	*txt_SO;
	char	*txt_WE;
	char	*txt_EA;
	int		txt_width;
	int		txt_height;
	t_clr	clr_floor;
	t_clr	clr_ceiling;
}				t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;

	t_map	*map;
}				t_game;

int		error_print(char *error_message);
void	error_print_exit(char *error_message, t_game *game);

int		free_game(t_game *game);
int		free_map(t_map *map);
int		free_str_arr(char **arr);

int		init_empty_struct(t_game *game);
int		arg_checker(int argc, char **argv, t_game *game);

int		parser(t_game *game);
int		print_map(char **map);
int		print_values(t_game *game);


#endif