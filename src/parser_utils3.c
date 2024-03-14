/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:16:52 by vbartos           #+#    #+#             */
/*   Updated: 2024/03/14 16:21:31 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Initializes the empty textures in the game structure.
 * 
 * @param game The game structure.
 */
void	init_empty_textures(t_game *game)
{
	game->map->mlx_txt_no = NULL;
	game->map->mlx_txt_so = NULL;
	game->map->mlx_txt_we = NULL;
	game->map->mlx_txt_ea = NULL;
}

/**
 * Loads and verifies the textures for the game.
 * 
 * Uses the mlx_load_png to verify that the parsed path to the textures
 * is working. If yes, assigns the textures. If no, prints an error message and
 * exits the program.
 * 
 * @param game The game structure.
 */
void	load_and_verify_textures(t_game *game)
{
	game->map->mlx_txt_no = mlx_load_png(game->map->txt_no);
	game->map->mlx_txt_so = mlx_load_png(game->map->txt_so);
	game->map->mlx_txt_we = mlx_load_png(game->map->txt_we);
	game->map->mlx_txt_ea = mlx_load_png(game->map->txt_ea);
	if (!(game->map->mlx_txt_no) || !(game->map->mlx_txt_so)
		|| !(game->map->mlx_txt_we) || !(game->map->mlx_txt_ea))
		error_print_exit(ERR_TXT_OPEN, game);
}

/**
 * Converts a string representation of a number to an integer.
 * 
 * On top of the regular atoi() functionality, it checks whether the converted
 * number is bigger than INTMAX. If so, it returns -1 via pointer for later
 * free() calls.
 *
 * @param nptr The string to be converted.
 * @param intmax_check A pointer to an integer that will be set to -1 if the
 * converted number exceeds INT32_MAX.
 * @return The converted integer value.
 */
int	clr_atoi(const char *nptr, int *intmax_check)
{
	int						i;
	unsigned long long int	num;

	i = 0;
	num = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t'
		|| nptr[i] == '\f' || nptr[i] == '\r'
		|| nptr[i] == '\n' || nptr[i] == '\v')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	if (num > INT32_MAX)
		*intmax_check = -1;
	return ((int)num);
}
