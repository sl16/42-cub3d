#include "../inc/cub3d.h"

int	print_values(t_game *game)
{
	ft_printf("texture_NO: %s\n", game->map->texture_NO);
	ft_printf("texture_SO: %s\n", game->map->texture_SO);
	ft_printf("texture_WE: %s\n", game->map->texture_WE);
	ft_printf("texture_EA: %s\n", game->map->texture_EA);
	return (0);
}

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