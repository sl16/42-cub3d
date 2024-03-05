/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:37:55 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/05 13:58:49 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *) param;
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		exit(EXIT_FAILURE);
	}
	cast_rays_3d(game, game->player, game->ray);
	cast_rays_2d(game, game->player, game->ray);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_struct(game);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	t_game	game;

	init_game_struct(&game);
	print_grid(game.map->grid, game.map->map_height);
	if (!init_mlx42(&game))
		return (EXIT_FAILURE);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop_hook(game.mlx, &handle_key_actions, &game);
	mlx_loop(game.mlx);
	free_game_struct(&game);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
