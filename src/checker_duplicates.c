/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_duplicates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:03:22 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/25 17:27:28 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief Checks if a value appears as a duplicate in the parsed file.
 * 
 * This function iterates through the parsed file and counts the number of
 * occurrences of the given value.
 *  
 * @param value The value to check for duplicates.
 * @param game A pointer to the game structure.
 */
static void	check_if_duplicate(char *value, t_game *game)
{
	char	**parsed_file;
	int		i;
	int		j;
	int		count;

	parsed_file = game->map->parsed_file;
	i = 0;
	count = 0;
	while (parsed_file[i] != NULL)
	{
		j = 0;
		j = increment_if_space(parsed_file[i], j);
		if (ft_strncmp(parsed_file[i] + j, value, ft_strlen(value)) == 0
			&& is_space(parsed_file[i][j + ft_strlen(value)]))
			count++;
		i++;
	}
	if (count < 1)
		error_print_exit(ERR_MISSING_VALUE, game);
	else if (count > 1)
		error_print_exit(ERR_DUP_VALUE, game);
}

/**
 * Checks for duplicate entries in the game configuration.
 * 
 * @param game The game structure containing the configuration data.
 */
void	checker_duplicates(t_game *game)
{
	check_if_duplicate("NO", game);
	check_if_duplicate("SO", game);
	check_if_duplicate("WE", game);
	check_if_duplicate("EA", game);
	check_if_duplicate("F", game);
	check_if_duplicate("C", game);
}
