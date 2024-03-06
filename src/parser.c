#include "../inc/cub3d.h"

/**
 * @brief Parses a file and stores its contents in the game's map structure.
 * 
 * This function reads the file line by line using the `get_next_line` function
 * and concatenates each line into a single string. The concatenated string is
 * then split into an array of strings using the `ft_split` function and the
 * newline symbol as the delimiter. The resulting array is stored in the
 * `parsed_file` field of the game's map structure.
 * 
 * @param game A pointer to the game structure.
 * @return 0 on success.
 */
static int	file_parser(t_game *game)
{
	char	*line;
	char	*concat;
	char	*temp;
	int		i;

	line = get_next_line(game->map->fd);
	temp = ft_strdup("");
	i = 0;
	while (line)
	{
		concat = ft_strjoin(temp, line);
		free(temp);
		free(line);
		temp = concat;
		line = get_next_line(game->map->fd);
		i++;
	}
	close(game->map->fd);
	game->map->parsed_file = ft_split(temp, '\n');
	free(temp);
	return (0);
}

/**
 * Parses the game values from the parsed_file array. Omits leading and trailing
 * whitespaces and searches for the value inside the text.
 * 
 * @param value The value to be parsed.
 * @param parsed_file The array of strings to be parsed.
 * @return The parsed value as a substring.
 */
static char	*value_parser(char *value, char **parsed_file)
{
	int		i;
	int		j;
	int		str_start;
	int		str_end;

	i = 0;
	while (parsed_file[i] != NULL)
	{
		j = 0;
		j = increment_if_space(parsed_file[i], j);
		str_start = j;
		str_end = ft_strlen(parsed_file[i]);
		if (ft_strncmp(parsed_file[i] + j, value, ft_strlen(value)) == 0)
		{
			j += ft_strlen(value);
			j = increment_if_space(parsed_file[i], j);
			str_start = j;
			while (parsed_file[i][j] != '\0' && !is_space(parsed_file[i][j]))
				j++;
			str_end = j;
			break ;
		}
		i++;
	}
	return (ft_substr(parsed_file[i], str_start, (str_end - str_start)));
}

/**
 * Finds and parses and sets the floor or ceiling color based on the value. 
 * The parsed RGB values are then stored in the map structure.
 *
 * @param value The value to be parsed.
 * @param parsed_file The parsed file contents.
 * @param game The game structure.
 */
static void	clr_parser(char *value, char **parsed_file, t_game *game)
{
	char	*rgb;
	char	**split_rgb;

	rgb = value_parser(value, parsed_file);
	split_rgb = ft_split(rgb, ',');
	free(rgb);
	if (value[0] == 'F')
	{
		game->map->clr_floor.r = ft_atoi(split_rgb[0]);
		game->map->clr_floor.g = ft_atoi(split_rgb[1]);
		game->map->clr_floor.b = ft_atoi(split_rgb[2]);
		game->map->clr_floor.a = 0xFF;
	}
	else if (value[0] == 'C')
	{
		game->map->clr_ceiling.r = ft_atoi(split_rgb[0]);
		game->map->clr_ceiling.g = ft_atoi(split_rgb[1]);
		game->map->clr_ceiling.b = ft_atoi(split_rgb[2]);
		game->map->clr_ceiling.a = 0xFF;
	}
	free_str_arr(split_rgb);
}

/**
 * Finds the start of the map in the parsed file and assigns it to the map
 * variable.
 * If the map is not found, it prints an error message and exits the program.
 *
 * @param map The map structure.
 * @param game The game structure.
 */
static void	find_map_in_file(t_map *map, t_game *game)
{
	int	map_start;
	int	i;
	int	j;

	map_start = -1;
	i = 0;
	while (map->parsed_file[i] != NULL && map_start == -1)
	{
		j = 0;
		while (map->parsed_file[i][j] != '\0')
		{
			if (map->parsed_file[i][j] != '1'
				&& !is_space(map->parsed_file[i][j]))
				break ;
			j++;
			if (map->parsed_file[i][j] == '\0')
				map_start = i;
		}
		i++;
	}
	if (map_start == -1)
		error_print_exit(ERR_MAP_NOT_FOUND, game);
	map->grid = &map->parsed_file[map_start];
}

/**
 * @brief Parses the game configuration file and initializes the game map.
 * 
 * This function reads the game configuration file and extracts the necessary
 * information such as texture paths, colors, and the game map.
 * It calls various helper functions to parse different sections of the file
 * and store the extracted values in the map struct. If any required values
 * are missing or invalid, it prints an error message and exits the program.
 * 
 * @param game A pointer to the game struct.
 * @return 0 on success.
 */
int	parser(t_game *game)
{
	t_map	*map;

	file_parser(game);
	map = game->map;
	map->txt_no = value_parser("NO", map->parsed_file);
	map->txt_so = value_parser("SO", map->parsed_file);
	map->txt_we = value_parser("WE", map->parsed_file);
	map->txt_ea = value_parser("EA", map->parsed_file);
	clr_parser("F", map->parsed_file, game);
	clr_parser("C", map->parsed_file, game);
	if (!map->txt_no || !map->txt_so || !map->txt_we || !map->txt_ea
		|| map->clr_ceiling.rgba == 0 || map->clr_floor.rgba == 0)
		error_print_exit(ERR_MISSING_VALUE, game);
	find_map_in_file(map, game);
	get_map_dimensions(map);
	copy_map(map, game);
	return (0);
}
