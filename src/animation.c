#include "../inc/cub3d.h"

/**
 * Code by Pulgamecanica: https://pulgamecanica.herokuapp.com/posts/mlx42-intro.
 * Converts the given RGBA values to a single integer value via bitshifting.
 *
 * @param r The red component value (0-255).
 * @param g The green component value (0-255).
 * @param b The blue component value (0-255).
 * @param a The alpha component value (0-255).
 * @return The combined RGBA value as an integer.
 */
static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * Code by Pulgamecanica: https://pulgamecanica.herokuapp.com/posts/mlx42-intro.
 * Retrieves the pixel color at the specified coordinates from an image.
 *
 * @param image The image to retrieve the pixel color from.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The color of the pixel at the specified coordinates.
 * If the coordinates are out of bounds, returns 0xFF000000
 * (transparent in ARGB format).
 */
static int32_t	mlx_get_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x > img->width || y > img->height)
		return (0xFF000000);
	pixelstart = img->pixels + (y * img->width + x) * 4;
	return (get_rgba(*(pixelstart), *(pixelstart + 1), *(pixelstart + 2),
			*(pixelstart + 3)));
}

/**
 * Code by Pulgamecanica: https://pulgamecanica.herokuapp.com/posts/mlx42-intro.
 * Checks if the given pixel coordinates are valid within the image dimensions
 * and if the pixel color at that position is not equal to 0.
 *
 * @param img The image to check the pixel in.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return 1 if the pixel is valid and not equal to 0, 0 otherwise.
 */
static int	put_pixel_valid(mlx_image_t *img, uint32_t x, uint32_t y)
{
	return (x < img->width && y < img->height && mlx_get_pixel(img, x, y) != 0);
}

/**
 * Code by Pulgamecanica: https://pulgamecanica.herokuapp.com/posts/mlx42-intro.
 * Puts the pixels from the source image onto the destination image at the
 * specified position.
 *
 * @param dst The destination image.
 * @param src The source image.
 * @param x The x-coordinate of the position where the source image will be
 * placed on the destination image.
 * @param y The y-coordinate of the position where the source image will be
 * placed on the destination image.
 */
static void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			if (put_pixel_valid(src, i, j))
				mlx_put_pixel(dst, x + i, y + j, mlx_get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}

/**
 * Plays an animation on the game screen.
 *
 * @param game The game structure.
 */
void	play_animation(t_game *game)
{
	static float	animation_counter;

	animation_counter += 0.2;
	if (animation_counter <= 30)
		put_img_to_img(game->image, game->animation, 1100,
			30 + animation_counter);
	else
	{
		put_img_to_img(game->image, game->animation, 1100,
			90 - animation_counter);
		if (animation_counter >= 60)
			animation_counter = 0;
	}
}
