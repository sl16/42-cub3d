#include "../inc/cub3d.h"

int		error_print(char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	return (0);
}

void	error_print_exit(char *error_message, t_game *game)
{
	ft_printf("Error\n%s\n", error_message);
	if (game)
		free_game(game);
	exit(1);
}