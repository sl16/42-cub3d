#include "../inc/cub3d.h"

int	is_space(char input)
{
	if (!(7 <= input && input <= 13) && input != 32)
		return (0);
	else
		return (1);
}

int	increment_if_space(char *input, int i)	
{
	while (input[i] != '\0')
	{
		if (!is_space(input[i]))
			break;
		i++;
	}
	return (i);
}

void	get_map_dimensions(t_map *map)
{
	int	max_width;
	int i;
	int	j;

	max_width = 0;
	i = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
			j++;
		if (j > max_width)
			max_width = j;
		i++;
	}
	map->width = max_width;
	map->height = i;
}