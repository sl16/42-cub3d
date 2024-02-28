/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:19:52 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/28 11:55:11 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	free_game_struct(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->map_height)
	{
		if (game->map->grid[i])
			free(game->map->grid[i]);
		i++;
	}
	if (game->map->grid)
		free(game->map->grid);
	if (game->map)
		free(game->map);
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
}
