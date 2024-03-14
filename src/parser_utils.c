/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:16:46 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/14 14:16:47 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Checks if the given character is a space. The function handles any of the
 * whitespace characters.
 * The function is intended for use in if statements, therefore 1 is returned
 * on success.
 *
 * @param input The character to check.
 * @return 1 if the character is a space, 0 otherwise.
 */
int	is_space(char input)
{
	if (!(7 <= input && input <= 13) && input != 32)
		return (0);
	else
		return (1);
}

/**
 * Checks if the given input character represents a wall.
 * The function is intended for use in if statements, therefore 1 is returned
 * on success.
 * 
 * @param input The character to be checked.
 * @return 1 if the character represents a wall, 0 otherwise.
 */
int	is_wall(char input)
{
	if (input != '1')
		return (0);
	else
		return (1);
}

/**
 * Increments the index 'i' until a non-space character is encountered in the
 * input string.
 * 
 * @param input The input string to be checked.
 * @param i The current index in the input string.
 * @return The updated index after skipping all consecutive space characters.
 */
int	increment_if_space(char *input, int i)
{
	while (input[i] != '\0')
	{
		if (!is_space(input[i]))
			break ;
		i++;
	}
	return (i);
}

/**
 * Finds the index of the last non-space character in the input string.
 *
 * @param input The input string to search.
 * @return The index of the last non-space character, or -1 if no non-space
 * character is found.
 */
int	find_last_char(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && is_space(input[i]))
		i--;
	if (i >= 0)
		return (i);
	else
		return (-1);
}

/**
 * @brief Calculates the dimensions of the map.
 * 
 * This function iterates through the map array and determines the maximum width
 * and height of the map. The width is determined by finding the longest row in
 * the map, while the height is determined by counting the number of rows.
 * The calculated dimensions are stored in the map structure.
 * 
 * @param map The map structure.
 */
void	get_map_dimensions(t_map *map)
{
	int	max_width;
	int	i;
	int	j;

	max_width = 0;
	i = 0;
	while (map->grid[i] != NULL)
	{
		j = 0;
		while (map->grid[i][j] != '\0')
			j++;
		if (j > max_width)
			max_width = j;
		i++;
	}
	map->map_width = max_width;
	i--;
	while (line_has_spaces_only(map->grid[i]))
		i--;
	map->map_height = i + 1;
}
