#include "../inc/cub3d.h"

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