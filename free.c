/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:19:52 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/26 16:20:06 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	free_game_struct(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->map_height)
	{
		free(game->map->grid[i]);
		i++;
	}
	free(game->map->grid);
	free(game->map);
	free(game->player);
	free(game->ray);
}
