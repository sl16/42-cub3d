#include "../inc/cub3d.h"

// code: courtesy of Pulgamecanica
// (https://pulgamecanica.herokuapp.com/posts/mlx42-intro)

int get_rgba(int r, int g, int b, int a)
{
  return (r << 24 | g << 16 | b << 8 | a);
}

int32_t mlx_get_pixel(mlx_image_t* image, uint32_t x, uint32_t y)
{
  if (x > image->width || y > image->height)
    return 0xFF000000;
  uint8_t* pixelstart = image->pixels + (y * image->width + x) * 4;
  return get_rgba(*(pixelstart), *(pixelstart + 1),
    * (pixelstart + 2), *(pixelstart + 3));
}

int put_pixel_valid(mlx_image_t* img, uint32_t x, uint32_t y)
{
  return (x < img->width && y < img->height && mlx_get_pixel(img, x, y) != 0);
}

void  put_img_to_img(mlx_image_t* dst, mlx_image_t* src, int x, int y)
{
	uint32_t i;
 	uint32_t j;

  i = 0;
  while(i < src->width) {
    j = 0;
    while (j < src->height) {
      if (put_pixel_valid(src, i, j))
        mlx_put_pixel(dst, x + i, y + j, mlx_get_pixel(src, i, j));
      j++;
    }
    i++;
  }
}

void	play_animation(t_game *game)
{
	static float animation_counter = 0;
	animation_counter+= 0.2;
	if (animation_counter <= 30)
		put_img_to_img(game->image, game->animation, 600, 300 + animation_counter);
	else if (animation_counter <= 60)
	{
		put_img_to_img(game->image, game->animation, 600, 360 - animation_counter);
		if (animation_counter == 60)
			animation_counter = 0;
	}
}