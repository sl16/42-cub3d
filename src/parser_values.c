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
 * Parses the game values from the parsed_file array. Omits leading whitespaces
 * and searches for the value inside the text.
 * 
 * Note: this function does not omit trailing whitespaces after the first value
 * is found, because the colors value could be input with spaces in between
 * (e.g. 'C  255,255  ,   255'). 
 * 
 * @param value The value to be parsed.
 * @param parsed_file The array of strings to be parsed.
 * @return The parsed value as a substring.
 */
static char	*value_parser_for_clrs(char *value, char **parsed_file)
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
			while (parsed_file[i][j] != '\0')
				j++;
			str_end = j;
			break ;
		}
		i++;
	}
	return (ft_substr(parsed_file[i], str_start, (str_end - str_start)));
}

/**
 * Sets the floor color of the game map based on the RGB values provided.
 * 
 * @param split_rgb An array of strings representing the RGB values.
 * @param game      A pointer to the game structure.
 */
static void	set_floor_clr(char **split_rgb, t_game *game)
{
	int	i;

	i = 0;
	while (split_rgb[i] != NULL)
	{
		if (i == 0)
			game->map->clr_floor.r = ft_atoi(split_rgb[i]);
		else if (i == 1)
			game->map->clr_floor.g = ft_atoi(split_rgb[i]);
		else if (i == 2)
			game->map->clr_floor.b = ft_atoi(split_rgb[i]);
		i++;
	}
	game->map->clr_floor.a = 0xFF;
}

/**
 * Sets the ceiling color of the game map based on the RGB values provided.
 * 
 * @param split_rgb An array of strings representing the RGB values.
 * @param game      A pointer to the game structure.
 */
static void	set_ceiling_clr(char **split_rgb, t_game *game)
{
	int	i;

	i = 0;
	while (split_rgb[i] != NULL)
	{
		if (i == 0)
			game->map->clr_ceiling.r = ft_atoi(split_rgb[i]);
		else if (i == 1)
			game->map->clr_ceiling.g = ft_atoi(split_rgb[i]);
		else if (i == 2)
			game->map->clr_ceiling.b = ft_atoi(split_rgb[i]);
		i++;
	}
	game->map->clr_ceiling.a = 0xFF;
}

/**
 * Finds and parses and sets the floor or ceiling color based on the value.
 * 
 * The function also validates the RGB colors. It iterates through the array of
 * color values and checks if any value contains anything but digits. If it does
 * contain anything else, it prints an error message and exits the program.
 * In the case of overflowing values (256+), the value is correctly set using
 * modulo operation by ft_atoi() in set_floor_clr() and set_ceiling_clr().
 * 
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
	int		i;
	int		j;

	rgb = value_parser_for_clrs(value, parsed_file);
	split_rgb = ft_split(rgb, ',');
	free(rgb);
	i = -1;
	while (split_rgb[++i] != NULL)
	{
		j = -1;
		while (split_rgb[i][++j] != '\0')
		{
			if (!ft_isdigit(split_rgb[i][j]))
				error_print_exit(ERR_COLOR, game);
		}
	}
	if (value[0] == 'F')
		set_floor_clr(split_rgb, game);
	else if (value[0] == 'C')
		set_ceiling_clr(split_rgb, game);
	free_str_arr(split_rgb);
}
