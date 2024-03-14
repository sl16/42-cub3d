/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbartos <vbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:23:00 by aulicna           #+#    #+#             */
/*   Updated: 2024/03/14 12:34:29 by vbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * This function frees each individual string in the array and then frees
 * the array itself.
 * 
 * @param arr The string array to be freed.
 * @return 0 on success.
 */
int	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

/**
 * Frees the memory allocated for a map structure.
 * 
 * @param map The map structure to be freed.
 * @return 0 on success.
 */
int	free_map(t_map *map)
{
	if (map->grid)
		free_str_arr(map->grid);
	if (map->parsed_file)
		free_str_arr(map->parsed_file);
	if (map->txt_no)
		free(map->txt_no);
	if (map->txt_so)
		free(map->txt_so);
	if (map->txt_we)
		free(map->txt_we);
	if (map->txt_ea)
		free(map->txt_ea);
	if (map->mlx_txt_no)
		mlx_delete_texture(map->mlx_txt_no);
	if (map->mlx_txt_so)
		mlx_delete_texture(map->mlx_txt_so);
	if (map->mlx_txt_we)
		mlx_delete_texture(map->mlx_txt_we);
	if (map->mlx_txt_ea)
		mlx_delete_texture(map->mlx_txt_ea);
	free(map);
	return (0);
}

/**
 * This function frees the memory allocated for the game and its map
 * in the parser part of the code.
 * It first checks if the game's map is not NULL and calls the `free_map`
 * function to free the map.
 * Then, it frees the memory allocated for the game struct itself.
 * 
 * @param game A pointer to the game structure.
 * @return 0 on success.
 */
int	free_game_parser(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game)
		free(game);
	return (0);
}

/**
 * @brief	Frees all the dynamically allocated memory in the program.
 * 
 * It checks and frees map, player and ray structs. Then it handles the closing
 * of mxl and finally frees the game struct.
 * 
 * @param	game	pointer to the game structure
 */
void	free_game_full(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	mlx_delete_image(game->mlx, game->image);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	if (game)
		free(game);
}
