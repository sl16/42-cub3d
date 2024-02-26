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
			{
				start_found++;
				map->start_x = j;
				map->start_y = i;
				map->start_dir = ft_strdup(&ch);
			}
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

// static void	check_side_walls(t_map *map, t_game *game)
// {
// 	int i;
// 	int	j;

// 	i = 1;
// 	while (i < map->height - 1)
// 	{
// 		j = 0;
// 		j = increment_if_space(map->map[i], j);
// 		if (map->map[i][j] != '1')
// 			error_print_exit(ERR_MAP_NOT_CLOSED, game);
// 		while (!is_space(map->map[i][j]) && map->map[i][j] != '\0')
// 			j++;
// 		printf("x: %d, y: %d \n", j, i);
// 		if (map->map[i][j - 1] != '1')
// 			error_print_exit(ERR_MAP_NOT_CLOSED, game);
// 		i++;
// 	}
// }

// static void	check_corners(t_map *map, t_game *game)
// {
// 	int 	i;
// 	size_t	j;

// 	i = 1;
// 	while (i < map->height - 1)
// 	{
// 		j = 0;
// 		j = increment_if_space(map->map[i], j);
// 		while (j != '\0')
// 		{
// 			printf("H: %d, W: %d \n", i, (int)j);
// 			if ((ft_strlen(map->map[i]) > ft_strlen(map->map[i - 1]))
// 				&& j > ft_strlen(map->map[i - 1]) && map->map[i][j] != '1')
// 				error_print_exit(ERR_MAP_CORNERS, game);
// 			if ((ft_strlen(map->map[i]) > ft_strlen(map->map[i + 1]))
// 				&& j > ft_strlen(map->map[i + 1]) && map->map[i][j] != '1')
// 				error_print_exit(ERR_MAP_CORNERS, game);
// 			j++;
// 		}
// 	}
// }

// static void check_adjacent(int x, int y, t_map *map, t_game *game)
// {
// 	printf("x: %d, y: %d \n", x, y);
// 	if (map->map[y][x + 1] != '1' || !is_space(map->map[y][x + 1]))
// 		error_print_exit(ERR_MAP_ADJACENT, game);
// 	if (map->map[y][x - 1] != '1' || !is_space(map->map[y][x - 1]))
// 		error_print_exit(ERR_MAP_ADJACENT, game);
// 	if (map->map[y + 1][x] != '1' || !is_space(map->map[y + 1][x]))
// 		error_print_exit(ERR_MAP_ADJACENT, game);
// 	if (map->map[y - 1][x] != '1' || !is_space(map->map[y - 1][x]))
// 		error_print_exit(ERR_MAP_ADJACENT, game);

// }

// static void	check_inner_walls(t_map *map, t_game *game)
// {
// 	int i;
// 	int	j;

// 	i = 1;
// 	while (i < map->height - 1)
// 	{
// 		j = 0;
// 		j = increment_if_space(map->map[i], j);
// 		while (map->map[i][j] != '\0')
// 		{
// 			if (!is_space(map->map[i][j]))
// 				j++;
// 			if (is_space(map->map[i][j]))
// 				check_adjacent(j, i, map, game);
// 			j++;
// 		}
// 		i++;
// 	}
// }

static int	check_floodfill(int x, int y, t_map *map)
{
	if (map->map[y][x] == 0)
	return (1);
}


void	checker_map(t_map *map, t_game *game)
{
	check_chars(map, game);
	check_top_and_bottom_walls(map, game);
	if (check_floodfill(map->start_x, map->start_y, map) == 1)
		error_print_exit(ERR_MAP_ADJACENT, game);
	// check_side_walls(map, game);
	// // check_corners(map, game);
	// check_inner_walls(map, game);
}
