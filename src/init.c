#include "../inc/cub3d.h"

int	init_empty_struct(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		error_print_exit(ERR_MALLOC_MAP, game);
	game->map->fd = 0;
	game->map->parsed_file = NULL;
	game->map->map = NULL;
	game->map->texture_NO = NULL;
	game->map->texture_SO = NULL;
	game->map->texture_WE = NULL;
	game->map->texture_EA = NULL;
	game->map->texture_width = 0;
	game->map->texture_height = 0;
	game->map->color_floor = 0;
	game->map->color_ceiling = 0;
	return (0);
}