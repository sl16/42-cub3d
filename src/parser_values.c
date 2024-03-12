#include "../inc/cub3d.h"

/**
 * Parses the game values from the parsed_file array. Omits leading and trailing
 * whitespaces and searches for the value inside the text.
 * 
 * @param value The value to be parsed.
 * @param parsed_file The array of strings to be parsed.
 * @return The parsed value as a substring.
 */
char	*value_parser(char *value, char **parsed_file)
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
void	clr_parser(char *value, char **parsed_file, t_game *game)
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
 * Checks if the provided texture files exist and can be opened.
 * 
 * @param game The game structure.
 */
void	files_exist(t_game *game)
{
	int	fd;

	fd = open(game->map->txt_no, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
	fd = open(game->map->txt_ea, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
	fd = open(game->map->txt_we, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
	fd = open(game->map->txt_so, O_RDONLY);
	if (fd == -1)
		error_print_exit(ERR_TXT_OPEN, game);
	close(fd);
}
