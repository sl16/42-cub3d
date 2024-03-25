/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:16:31 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/25 16:40:57 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Prints an error message.
 *
 * @param error_message The error message to be printed.
 * @return 0 indicating the error has been printed.
 */
int	error_print(const char *error_message)
{
	write(2, "Error\n", 6);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	return (0);
}

/**
 * Prints an error message, frees allocated memory and exits the program.
 *
 * @param error_message The error message to be printed.
 * @param game The game structure pointer (can be NULL).
 */
void	error_print_exit(char *error_message, t_game *game)
{
	write(2, "Error\n", 6);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	if (game)
		free_game_parser(game);
	exit(1);
}
