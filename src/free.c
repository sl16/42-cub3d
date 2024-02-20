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
		free_str_arr(map->parsed_file);
	if (map->txt_NO)
		free(map->txt_NO);
	if (map->txt_SO)
		free(map->txt_SO);
	if (map->txt_WE)
		free(map->txt_WE);
	if (map->txt_EA)
		free(map->txt_EA);
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