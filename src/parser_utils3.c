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

/**
 * Converts a string representation of a number to an integer.
 * 
 * On top of the regular atoi() functionality, it checks whether the converted
 * number is bigger than INTMAX. If so, it returns -1 via pointer for later
 * free() calls.
 *
 * @param nptr The string to be converted.
 * @param intmax_check A pointer to an integer that will be set to -1 if the
 * converted number exceeds INT32_MAX.
 * @return The converted integer value.
 */
int	clr_atoi(const char *nptr, int *intmax_check)
{
	int						sign;
	int						i;
	unsigned long long int	num;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t'
		|| nptr[i] == '\f' || nptr[i] == '\r'
		|| nptr[i] == '\n' || nptr[i] == '\v')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	if (num > INT32_MAX)
		*intmax_check = -1;
	return ((int)num);
}
