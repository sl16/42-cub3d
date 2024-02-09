#include "../inc/cub3d.h"

int	print_values(t_game *game)
{
	ft_printf("texture_NO: %s\n", game->map->txt_NO);
	ft_printf("texture_SO: %s\n", game->map->txt_SO);
	ft_printf("texture_WE: %s\n", game->map->txt_WE);
	ft_printf("texture_EA: %s\n", game->map->txt_EA);
	ft_printf("floor color: %d\n", game->map->clr_floor);
	ft_printf("ceiling color: %d\n", game->map->clr_ceiling);
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