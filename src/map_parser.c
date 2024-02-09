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

static int	value_parser(t_game *game)
{
	int		i;
	int		j;
	// char	**str_arr;

	i = 0;
	while (game->map->parsed_file[i] != NULL)
	{
		j = 0;
		while (game->map->parsed_file[i][j] == ' ')
			j++;
		if (ft_strncmp((*(game->map->parsed_file + i) + j), "NO", 2) == 0)
		{
			j += 2;
			while (game->map->parsed_file[i][j] == ' ')
				j++;
			game->map->texture_NO
				= ft_strdup((*(game->map->parsed_file + i) + j));
		}
		else if (ft_strncmp((*(game->map->parsed_file + i) + j), "SO", 2) == 0)
		{
			j += 2;
			while (game->map->parsed_file[i][j] == ' ')
				j++;
			game->map->texture_SO
				= ft_strdup((*(game->map->parsed_file + i) + j));
		}
		else if (ft_strncmp((*(game->map->parsed_file + i) + j), "WE", 2) == 0)
		{
			j += 2;
			while (game->map->parsed_file[i][j] == ' ')
				j++;
			game->map->texture_WE
				= ft_strdup((*(game->map->parsed_file + i) + j));
		}
		else if (ft_strncmp((*(game->map->parsed_file + i) + j), "EA", 2) == 0)
		{
			j += 2;
			while (game->map->parsed_file[i][j] == ' ')
				j++;
			game->map->texture_EA
				= ft_strdup((*(game->map->parsed_file + i) + j));
		}
		i++;
	}

	return (0);
}

int	map_parser(t_game *game)
{
	file_parser(game);
	value_parser(game);

	return (0);
}