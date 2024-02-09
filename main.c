#include "./inc/cub3d.h"


int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error_print_exit(ERR_MALLOC_GAME, NULL);
	init_empty_struct(game);
	arg_checker(argc, argv, game);
	map_parser(game);
	print_values(game);
	ft_printf("\n\n");
	print_map(game->map->parsed_file);
	// map_checker(argc, argv, game);

	return (0);
}