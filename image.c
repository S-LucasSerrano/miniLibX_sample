#include "mlx_sample.h"

/* Returns an image of <width> x <height> black pixels. */
t_image ft_new_image(void* mlx, int width, int height)
{
	t_image img;

	/* mlx function that creates and returns a pointer
	to an image of the given width and height */
	img.reference = mlx_new_image(mlx, width, height);
	img.size.x = width;
	img.size.x = height;

	/* mlx function that returs a pointer to the first pixel of the given image.
	* ¡Pixels are not stored in a 2D table, just a single char[] array!
	* the fuction also saves in the given pointers:
	*	the bits per pixel (each pixel is usually 4 chars of the array),
	* 	the line size of the pixels array  (the amount of pixels in one line of the image)
	* 	and the endian (info of how the colors are stored) */
	img.pixels = mlx_get_data_addr(img.reference, &img.bits_per_pixel, &img.line_size, &img.endian);

	return (img);
}

/* Returns an image with the sprite found in <path> */
t_image ft_new_sprite(void *mlx, char *path)
{
	t_image img;
	
	/* mlx function that creates and image that contains the xmp file found in the given path.
	* It also saves the width and height of the image in the pointers passed as parameters */
	img.reference = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels  = mlx_get_data_addr(img.reference, &img.bits_per_pixel, &img.line_size, &img.endian);
	return (img);
}
