/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:16:42 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/14 14:16:43 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if ((map->parsed_file[i][j] != '1'
				&& !is_space(map->parsed_file[i][j]))
				|| line_has_spaces_only(map->parsed_file[i]))
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
	load_and_verify_textures(game);
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
