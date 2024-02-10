#include "../inc/cub3d.h"

int	print_values(t_game *game)
{
	ft_printf("\n --- PARSED VALUES ---\n\n");
	ft_printf("texture_NO: %s\n", game->map->txt_NO);
	ft_printf("texture_SO: %s\n", game->map->txt_SO);
	ft_printf("texture_WE: %s\n", game->map->txt_WE);
	ft_printf("texture_EA: %s\n", game->map->txt_EA);
	ft_printf("floor color: %u, %u, %u, %u\n", game->map->clr_floor.r, game->map->clr_floor.g, game->map->clr_floor.b, game->map->clr_floor.a);
	ft_printf("ceiling color: %u, %u, %u, %u\n", game->map->clr_ceiling.r, game->map->clr_ceiling.g, game->map->clr_ceiling.b, game->map->clr_ceiling.a);
	return (0);
}

int	print_map(char **map)
{
	int i;

	i = 0;
	ft_printf("\n --- ORIGINAL FILE ---\n\n");
	while (map[i] != NULL)
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
	return (0);
}