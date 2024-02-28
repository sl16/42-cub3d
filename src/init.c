#include "../inc/cub3d.h"

/**
 * Initializes an empty game structure.
 * 
 * @param game The game structure to initialize.
 * @return 0 if successful, otherwise an error code.
 */
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
	game->map->width = 0;
	game->map->height = 0;
	game->map->txt_NO = NULL;
	game->map->txt_SO = NULL;
	game->map->txt_WE = NULL;
	game->map->txt_EA = NULL;
	game->map->txt_width = 0;
	game->map->txt_height = 0;
	game->map->clr_floor.rgba = 0;
	game->map->clr_ceiling.rgba = 0;
	game->map->start_dir = NULL;
	game->map->start_count = 0;
	game->map->start_x = -1;
	game->map->start_y = -1;
	return (0);
}