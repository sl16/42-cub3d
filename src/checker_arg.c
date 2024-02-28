#include "../inc/cub3d.h"

/**
 * Checks the command line arguments and and checks if the specified map file
 * exists and can be opened.
 * 
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @param game A pointer to the game structure.
 * @return 0 if successful.
 */
int	checker_arg(int argc, char **argv, t_game *game)
{
	int	len;

	if (argc != 2)
		error_print_exit(ERR_ARGC, game);
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		error_print_exit(ERR_ARGV, game);
	game->map->fd = open(argv[1], O_RDONLY);
	if (game->map->fd < 0)
		error_print_exit(ERR_OPEN, game);
	return (0);
}