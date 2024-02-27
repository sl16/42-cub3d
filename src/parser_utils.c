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

int	find_last_char(char *input)
{
	// int	original_i;
	// int	len_until_end;
	// int	len_spaces;
	// int	j;

	// original_i = i;
	// while (input[i] != '\0')
	// {
	// 	len_until_end = ft_strlen(input + i);
	// 	len_spaces = 0;
	// 	j = i;
	// 	while (is_space(input[j]))
	// 	{
	// 		len_spaces++;
	// 		j++;
	// 	}
	// 	if (len_until_end == len_spaces)
	// 		return (i);
	// 	i++;
	// }
	// return (original_i);

	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && is_space(input[i]))
		i--;
	if (i >= 0)
		return (i);
	else
		return (-1);
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