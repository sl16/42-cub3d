#include "../inc/cub3d.h"

/**
 * Prints an error message.
 *
 * @param error_message The error message to be printed.
 * @return 0 indicating the error has been printed.
 */
int	error_print(const char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	return (0);
}

/**
 * Prints an error message, frees allocated memory and exits the program.
 *
 * @param error_message The error message to be printed.
 * @param game The game structure pointer (can be NULL).
 */
void	error_print_exit(char *error_message, t_game *game)
{
	ft_printf("Error\n%s\n", error_message);
	if (game)
		free_game_parser(game);
	exit(1);
}
