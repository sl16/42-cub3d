/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:37:55 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 08:02:52 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_full(game);
		exit(EXIT_FAILURE);
	}
	cast_rays_3d(game, game->player, game->ray);
	cast_rays_2d(game, game->player, game->ray);
	play_animation(game);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		free_game_full(game);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error_print_exit(ERR_MALLOC_GAME, NULL);
	init_empty_struct(game);
	checker_arg(argc, argv, game);
	parser(game);
	checker_map(game->map, game);
	init_game_struct(game);
	print_grid(game->map->grid, game->map->map_height);
	if (!init_mlx42(game))
	{
		free_game_full(game);
		return (1);
	}
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop_hook(game->mlx, &handle_key_actions, game);
	mlx_loop(game->mlx);
	free_game_full(game);
	return (0);
}
