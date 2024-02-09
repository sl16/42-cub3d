#include "../inc/cub3d.h"

int	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

int	free_map(t_map *map)
{
	if (map->map)
		free_str_arr(map->map);
	if (map->texture_NO)
		free(map->texture_NO);
	if (map->texture_SO)
		free(map->texture_SO);
	if (map->texture_WE)
		free(map->texture_WE);
	if (map->texture_EA)
		free(map->texture_EA);
	free(map);
	return (0);
}

int	free_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game)
		free(game);
	return (0);
}