#include "../inc/cub3d.h"

/**
 * Checks if the map contains only permitted characters in the
 * required amount and saves the player's starting position to the map struct.
 * Removes the player symbol from the map, as the starting coordinates
 * are now saved.
 * 
 * @param x The x-coordinate of the character in the map.
 * @param y The y-coordinate of the character in the map.
 * @param map A pointer to the map struct.
 * @param game A pointer to the game struct.
 */
static void	check_chars(int x, int y, t_map *map, t_game *game)
{
	char			ch;

	ch = map->grid[y][x];
	if (ch != '0' && ch != '1' && ch != 'N' && ch != 'W' && ch != 'S'
		&& ch != 'E' && !is_space(ch))
		error_print_exit(ERR_MAP_CH_INVALID, game);
	if (ch == 'N' || ch == 'W' || ch == 'S' || ch == 'E')
	{
		map->start_count++;
		map->start_x = x;
		map->start_y = y;
		map->start_dir = ch;
		map->grid[y][x] = '0';
	}
}

/**
 * Checks if the top and bottom walls of the map are properly closed.
 * Leading whitespaces are ignored.
 *
 * @param map The map structure containing the map data.
 * @param game The game structure containing game-related data.
 */
static void	check_top_and_bottom_walls(t_map *map, t_game *game)
{
	int	i;

	i = 0;
	i = increment_if_space(map->grid[0], i);
	while (map->grid[0][i] != '\0')
	{
		if (map->grid[0][i] != '1' && !is_space(map->grid[0][i]))
			error_print_exit(ERR_MAP_NOT_CLOSED, game);
		i++;
	}
	i = 0;
	i = increment_if_space(map->grid[map->map_height - 1], i);
	while (map->grid[map->map_height - 1][i] != '\0')
	{
		if (map->grid[map->map_height - 1][i] != '1'
			&& !is_space(map->grid[map->map_height - 1][i]))
			error_print_exit(ERR_MAP_NOT_CLOSED, game);
		i++;
	}
}

/**
 * Checks if the left and right side walls of the map are properly closed.
 * Leading whitespaces are ignored. Trailing whitespaces are ignored.
 *
 * @param map The map structure containing the map data.
 * @param game The game structure containing game-related data.
 */
static void	check_side_walls(t_map *map, t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->map_height - 1)
	{
		j = 0;
		j = increment_if_space(map->grid[i], j);
		if (map->grid[i][j] != '1')
			error_print_exit(ERR_MAP_NOT_CLOSED, game);
		j = find_last_char(map->grid[i]);
		if (j == -1)
			error_print_exit(ERR_MAP_NOT_CLOSED, game);
		if (map->grid[i][j] != '1')
			error_print_exit(ERR_MAP_NOT_CLOSED, game);
		i++;
	}
}

/**
 * @brief Checks if the characters adjacent to a space are either a space or
 * a wall. The first and last lines and the first and last characters in
 * a line are ignored (as they are checked by other functions or the adjacency
 * and accessing their neighbours would cause a segfault).
 * 
 * @param x The x-coordinate of the position to check.
 * @param y The y-coordinate of the position to check.
 * @param map Pointer to the map structure.
 * @param game Pointer to the game structure.
 */
static void	check_spaces(int x, int y, t_map *map, t_game *game)
{
	if (y == 0 || y == map->map_height - 1 || !is_space(map->grid[y][x]))
		return ;
	if (x == 0)
		x++;
	if (x == (int) ft_strlen(map->grid[y]) - 1)
		x--;
	if (map->grid[y][x - 1] != '1' && !is_space(map->grid[y][x - 1]))
		error_print_exit(ERR_MAP_ADJACENT, game);
	if (map->grid[y][x + 1] != '1' && !is_space(map->grid[y][x + 1]))
		error_print_exit(ERR_MAP_ADJACENT, game);
	if (x < (int) ft_strlen(map->grid[y - 1])
		&& (map->grid[y - 1][x] != '1' && !is_space(map->grid[y - 1][x])))
		error_print_exit(ERR_MAP_ADJACENT, game);
	if (x < (int) ft_strlen(map->grid[y + 1])
		&& (map->grid[y + 1][x] != '1' && !is_space(map->grid[y + 1][x])))
		error_print_exit(ERR_MAP_ADJACENT, game);
}

/**
 * @brief Checks the validity of the map.
 * 
 * This function checks the map for whether all of the inner content is
 * properly enclosed with walls and contains only valid characters.
 * It also ensures that there is exactly one starting position in the map.
 * 
 * @param map The map structure.
 * @param game The game structure.
 */
void	checker_map(t_map *map, t_game *game)
{
	int	i;
	int	j;

	check_top_and_bottom_walls(map, game);
	check_side_walls(map, game);
	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		j = increment_if_space(map->grid[i], j);
		while (map->grid[i][j] != '\0')
		{
			check_chars(j, i, map, game);
			check_spaces(j, i, map, game);
			j++;
		}
		i++;
	}
	if (map->start_count != 1)
		error_print_exit(ERR_MAP_START, game);
	convert_spaces_to_walls(map);
}
