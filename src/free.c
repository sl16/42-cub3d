#include "../inc/cub3d.h"

/**
 * This function frees each individual string in the array and then frees
 * the array itself.
 * 
 * @param arr The string array to be freed.
 * @return 0 on success.
 */
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

/**
 * Frees the memory allocated for a map structure.
 * 
 * @param map The map structure to be freed.
 * @return 0 on success.
 */
int	free_map(t_map *map)
{
	if (map->parsed_file)
		free_str_arr(map->parsed_file);
	if (map->start_dir)
		free(map->start_dir);
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

/**
 * This function frees the memory allocated for the game and its map.
 * It first checks if the game's map is not NULL and calls the `free_map`
 * function to free the map.
 * Then, it frees the memory allocated for the game struct itself.
 * 
 * @param game A pointer to the game structure.
 * @return 0 on success.
 */
int	free_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game)
		free(game);
	return (0);
}