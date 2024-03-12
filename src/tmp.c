#include "../inc/cub3d.h"

// to be replaced in parser: function checking if the files exist via load_png + delete_texture (to free memory at the end too))
void	load_textures(t_map *map)
{
	map->mlx_txt_no = mlx_load_png(map->txt_no);	
	map->mlx_txt_so = mlx_load_png(map->txt_so);	
	map->mlx_txt_we = mlx_load_png(map->txt_we);	
	map->mlx_txt_ea = mlx_load_png(map->txt_ea);	
}