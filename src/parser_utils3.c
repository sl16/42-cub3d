#include "../inc/cub3d.h"

/**
 * Checks if the provided texture files exist and can be opened.
 * 
 * @param game The game structure.
 */
void	files_exist(t_game *game)
{
	int	fd;

	fd = open(game->map->txt_no, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
	fd = open(game->map->txt_ea, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
	fd = open(game->map->txt_we, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
	fd = open(game->map->txt_so, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
}
