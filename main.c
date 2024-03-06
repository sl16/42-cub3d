#include "./inc/cub3d.h"


int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error_print_exit(ERR_MALLOC_GAME, NULL);
	init_empty_struct(game);
	checker_arg(argc, argv, game);
	parser(game);
	checker_map(game->map, game);
	free_game(game);
	return (0);
}
