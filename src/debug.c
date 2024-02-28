#include "../inc/cub3d.h"

/**
 * Prints the values of various game parameters for debugging purposes.
 * 
 * @param game The game structure containing the map and other parameters.
 * @return 0 indicating successful execution.
 */
int	print_values(t_game *game)
{
	ft_printf("texture_NO: %s\n", game->map->txt_NO);
	ft_printf("texture_SO: %s\n", game->map->txt_SO);
	ft_printf("texture_WE: %s\n", game->map->txt_WE);
	ft_printf("texture_EA: %s\n", game->map->txt_EA);
	ft_printf("floor color: %u, %u, %u, %u\n", game->map->clr_floor.r, game->map->clr_floor.g, game->map->clr_floor.b, game->map->clr_floor.a);
	ft_printf("ceiling color: %u, %u, %u, %u\n", game->map->clr_ceiling.r, game->map->clr_ceiling.g, game->map->clr_ceiling.b, game->map->clr_ceiling.a);
	return (0);
}

/**
 * Prints the contents of a 2D array representing a map.
 *
 * @param map The 2D array representing the map.
 * @return 0 if successful.
 */
int	print_map(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
	return (0);
}