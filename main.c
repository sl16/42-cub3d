#include "./inc/cub3d.h"


int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error_print_exit(ERR_MALLOC_GAME, NULL);
	init_empty_struct(game);
	arg_checker(argc, argv, game);
	parser(game);
	ft_printf("\n --- ORIGINAL FILE ---\n\n");
	print_map(game->map->parsed_file);
	ft_printf("\n --- PARSED VALUES ---\n\n");
	print_values(game);
	ft_printf("\n --- PARSED MAP ---\n\n");
	print_map(game->map->map);
	free_game(game);
	// map_checker(argc, argv, game);

	return (0);
}