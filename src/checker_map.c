#include "../inc/cub3d.h"

static void	check_chars(t_map *map, t_game *game)
{
	int		start_found;
	int		i;
	int		j;
	char	ch;

	start_found = 0;
	i = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			ch = map->map[i][j];
			if (ch != '0' && ch != '1' && ch != 'N' && ch != 'W' && ch != 'S'
				&& ch != 'E' && !is_space(ch))
				error_print_exit(ERR_MAP_CH_INVALID, game);
			if (ch == 'N' || ch == 'W' || ch == 'S' || ch == 'E')
				start_found++;
			j++;
		}
		i++;
	}
	if (start_found != 1)
		error_print_exit(ERR_MAP_DUPLICATE, game);
}

static void	check_top_and_bottom_walls(t_map *map, t_game *game)
{
	int	i;

	i = 0;
	i = increment_if_space(map->map[0], i);
	while (map->map[0][i] != '\0')
	{
		if (map->map[0][i] != '1' && !is_space(map->map[0][i]))
					error_print_exit(ERR_MAP_NOT_CLOSED, game);
		i++;
	}
	i = 0;
	i = increment_if_space(map->map[map->height - 1], i);
	while (map->map[map->height - 1][i] != '\0')
	{
		if (map->map[map->height - 1][i] != '1'
			&& !is_space(map->map[map->height - 1][i]))
					error_print_exit(ERR_MAP_NOT_CLOSED, game);
		i++;
	}
}

static void	check_side_walls(t_map *map, t_game *game)
{
	int i;
	int	j;

	i = 1;
	while (i < map->height - 1)
	{
		j = 0;
		j = increment_if_space(map->map[i], j);
		if (map->map[i][j] != '1')
			error_print_exit(ERR_MAP_NOT_CLOSED, game);
		while (!is_space(map->map[i][j]) && map->map[i][j] != '\0')
			j++;
		if (map->map[i][j - 1] != '1')
			error_print_exit(ERR_MAP_NOT_CLOSED, game);
		i++;
	}
}

// floodfill --
// static void	check_inner_spaces(t_map *map, t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map->map[i] != NULL)
// 	{
// 		j = 0;
// 		j = increment_if_space(map->map[i], j);
// 		while (map->map[i][j] != '\0')
// 		{

// 			j++;
// 		}

// 		i++;
// 	}
// }

// add checks for all symbols
// add checks for duplicate values?
void	checker_map(t_map *map, t_game *game)
{
	check_chars(map, game);
	check_top_and_bottom_walls(map, game);
	check_side_walls(map, game);
	// check_inner_spaces(map, game);
}
