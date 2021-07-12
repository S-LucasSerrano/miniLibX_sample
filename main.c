#include "mlx_sample.h"

int main()
{
	// ----------

	// strcuts defined in the mlx_sample.h file
	t_program program;
	// mlx function that initialize the mlx and returns a pointer to it.
	program.mlx = mlx_init();
	// Open a window (window.c whitin this project)
	program.window = ft_new_window(program.mlx, 1980, 1080, "Hello world!");

	// ----------

	// Create a new image/sprite (image.c)
	program.sprite = ft_new_sprite(program.mlx, "block.xpm");
	// mlx function that prints an image into a window at the indicated coordinates
	mlx_put_image_to_window(program.mlx, program.window.reference,
		program.sprite.reference, program.sprite.position.x, program.sprite.position.y);

	// ----------

	// hook the input() (hooks.c) function to the the key pressed event
	mlx_key_hook(program.window.reference, *ft_input, &program);
	// hook a function to the loop (it would be called each frame)
	mlx_loop_hook(program.mlx, *ft_update, &program);

	// ----------

	// mlx constant loop that keeps the window open and detects the events and input
	mlx_loop(program.mlx);
}

/* 
* For more, see the manuals:
*	man /usr/share/man/man3/mlx.1
*	man /usr/share/man/man3/mlx_new_window.1
*	man /usr/share/man/man3/mlx_pixel_put.1
*	man /usr/share/man/man3/mlx_new_image.1
*	man /usr/share/man/man3/mlx_loop.1
*/