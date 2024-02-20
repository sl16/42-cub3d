#include "../inc/cub3d.h"

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
			break;
		}
		i++;
	}
	return (ft_substr(parsed_file[i], str_start, (str_end - str_start)));
}

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
				break;
			j++;
			if (map->parsed_file[i][j] == '\0')
				map_start = i;
		}
		i++;
	}
	if (map_start == -1)
		error_print_exit(ERR_MAP_NOT_FOUND, game);
	map->map = &map->parsed_file[map_start];
}

// add 'open' checks to texture to check if files actually exist?
// ERR_MISSING_VALUE checker for colours needs better condition (what if specified colors == 0?)
// current find_map_in_file doesn't work if first row of map not valid
// add further parsing checks for values
int	parser(t_game *game)
{
	t_map	*map;
	
	file_parser(game);
	map = game->map;
	map->txt_NO = value_parser("NO", map->parsed_file);
	map->txt_SO = value_parser("SO", map->parsed_file);
	map->txt_WE = value_parser("WE", map->parsed_file);
	map->txt_EA = value_parser("EA", map->parsed_file);
	clr_parser("F", map->parsed_file, game);
	clr_parser("C", map->parsed_file, game);
	if (!map->txt_NO || !map->txt_SO || !map->txt_WE || !map->txt_EA
		|| map->clr_ceiling.rgba == 0 || map->clr_floor.rgba == 0)
		error_print_exit(ERR_MISSING_VALUE, game);
	find_map_in_file(map, game);
	get_map_dimensions(map);
	return (0);
}