#include "../inc/cub3d.h"

/**
 * This function copies the map from `map_start` to `map->map` with padding
 * spaces to ensure that each row has a width equal to `map->width`.
 * It dynamically allocates memory for `map->map` and handles any memory
 * allocation errors.
 * 
 * @param map The map structure containing the original map and its dimensions.
 * @param game The game structure containing game-related information.
 */
void	copy_map(t_map *map, t_game *game)
{
	char	**map_start;
	int		i;
	int		j;

	map_start = map->map;
	map->map = NULL;
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		error_print_exit(ERR_MALLOC_MAP, game);
	i = -1;
	while (++i < map->height)
	{
		map->map[i] = malloc(sizeof(char *) * (map->width + 1));
		if (!map->map[i])
			error_print_exit(ERR_MALLOC_MAP, game);
		ft_strlcpy(map->map[i], map_start[i], ft_strlen(map_start[i]) + 1);
		j = ft_strlen(map->map[i]);
		while (j < map->width)
		{
			map->map[i][j] = ' ';
			j++;
		}
		map->map[i][j] = '\0';
	}
	map->map[i] = NULL;
}

/**
 * Converts spaces in the map to walls.
 * 
 * This function takes a pointer to a map structure and converts all whitespaces
 * (' ') in the map to walls ('1'). It iterates through each row and column of
 * the map and checks if the character is a space. If it is, it replaces it with
 * a wall character.
 * 
 * @param map A pointer to the map structure.
 */
void	convert_spaces_to_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (is_space(map->map[i][j]))
				map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}