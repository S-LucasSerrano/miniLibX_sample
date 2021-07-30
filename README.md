# miniLibX sample | slucas-s
I developed this sample project to play around with the basic functionalities of the miniLibX, the simple graphics library we use at 42. The final program is no more than a square moving around the screen, and there is more to the library than what is shown here. But I think all the fundamentals to get started with it are there: opening a window, creating and drawing images and managing events, hooks and input. And that it is especially useful if you are about to start the _so_long_ project, that is what is had in mind when developing this demo.

Check my own version of _so_long_ here:
https://github.com/S-LucasSerrano/so_long

---
* [Getting Started](#Getting-started)
* [Hooks](#Hooks)
* [Images](#Images)
* [Colors](#Colors)
* [Sample Program](#Sample-program)
* [Other References](#References)

---
### Getting started
Include the miniLibX:
```c
#include “mlx.h”
```
First, we need to initialize the mlx with ``mlx_init()``, that returns a pointer (void *) that we need to save because a lot of the library functions need it in order to work.
```c
void	*mlx_pointer = mlx_init();
```
Then, I open the window with the function ``mlx_new_window()`` that receives the mlx pointer, the window size, and the title that would be displayed on top. Returning a void pointer that is a reference to the opened window. Again, we need to save it for later use.
```c
void	*window = mlx_new_window(mlx_pointer, width, height, name);
```
I think is really useful to use a struct, especially for hooking functions later, that contains all of this data that your program would need:
```c
typedef struct	s_program
 {
	void	*mlx_pointer;
	void	*window;
	// … etc
}				t_program;
```
Finally, after setting up all you need for it to run, to start your program you need to call the ``mlx_loop()`` function. This is an infinite loop that would keep the program running, the window open, and would keep detecting the different events and calling the functions you’ve hooked to them. Any code written after the call to this function would never be executed.
```c
mlx_loop(mlx_pointer);
```

Because the miniLibX uses Appkit and MX11 you need to link them adding ``-lmlx -framework OpenGL -framework AppKit`` when you compile.

---
### Hooks
The miniLibX allows you to _‘hook’_ some of your functions to certain events. So when those events happen, like pressing a key, closing or focusing a window, a function of yours is called. The most generic way to do it is with the ``mlx_hook()`` function, which has the following prototype:
```c
mlx_hook(void *win_ptr, int event, int mask, int (*f)(), void *param);
```
It receives a pointer to the window that detects the event. The code of the event. The mask. A pointer to the function that would be called when the specified event triggers and a pointer that would be passed to your function as parameter. This means that the functions you hooked need to have a very specific prototype that looks like this:
````c
int	hooked_function(void *param);
````
It has to return an int, but this value is never used for anything as far as I know. As you can see, it only can receive a pointer to one variable, so what is usually done is pass a pointer to a struct that contains all the info that your function needs to work. What I do is make this function receive the whole program struct so it has access to the mlx pointer, the window and anything else it may need.

Here you have a list with all the events and masks. I’ve never really use masks for anything and don’t really know how they work, but, well, there they are:
https://harm-smits.github.io/42docs/libs/minilibx/events.html

Some useful events:
| Code | Event |
| ------- | -------- |
| 2 | Key pressed |
| 3 | Key released |
| 4 | Mouse pressed |
| 5 | Mouse released |
| 6 | Motion |
| 17 | Window closed |

By default when you close the window, you don’t stop the mlx_loop, so your program keeps infinitely running. You need to hook a function that makes ``exit(0);`` to the closing window event, for the program to end when the window is closed.

This other guide has more info about the miniLibX, and a lot of links beyond the mlx library, with useful resources for the cube 3D, fdf and fractal projects. Check it out:
https://github.com/qst0/ft_libgfx#the-graphics-branch

A couple of more things about hooks.

When you hook a function to a key related event, it needs to have a different prototype. Receiving an extra integer that indicates the key that has been pressed or released. To know the code of each key just print this value and press every key you want to know the code of.
````c
int	key_hooked_function(int keycode, void *param);
````

There are also more hook functions. The most important and useful is the ``mlx_loop_hook()`` that triggers each repetition of the loop. Calling your function each frame. For more on these other hook functions see: 
https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html#hooks

---
### Images
There are a couple of functions that create and return you a pointer to an image. Which you need to save to draw or manipulate that image later. Those functions are:
````c
void	*mlx_new_image(void *mlx_ptr, int width, int height);
void	*mlx_xpm_file_to_image(void *mlx_pointer, char *relative_path, int *width, int *height);
````
* ``mlx_new_image``. Creates an image of `width` x ``height`` pixels. All of them black by default.
* ``mlx_xmp_file_to_image``. Creates one that contains the .xpm image found in ``relative_path`` and saves its width and height in pixels to the given pointers. You can only use images in a xpm format. So here is the png to xmp converter I used: 
https://anyconv.com/png-to-xpm-converter/

To manipulate the pixels of an image you first need to call `mlx_get_data_addr()`.
````c
char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
````
This would return you a char array containing all pixels of the image and saving to the pointers passed as parameters the corresponding information about the image.
* ``bits_per_pixel``. It tells you the number of bits needed to represent a pixel color.
* ``size_line``. Because the pixels of the image are not stored in a 2D table but all in a row in a single array. This tells you how many pixels are in each line of your image, and each pixel is represented by 4 chars. Allowing you to get access to every pixel on the image with the following formula: _`X_position * 4 + Line_size * Y_position`_, that will give you the first char of the pixel.
* ``endian``. Can be either 0 or 1 depending on the system and it defines how colors are stored. For us in 42 I believe it’s always stored in the same way: the first character is blue, then green, red, and finally the alpha or transparency of the pixel. Each value goes from 0 to 255. _You have an example of how to use this and change every pixel of an image in the color.c file_.

How I save and manage it in this project is by creating a struct with all the data needed for an image.
````c
typedef struct	s_image
{
	void      *pointer;
	t_vector  size;
	char      *pixels;
	int       bits_per_pixel;
	int       line_size;
	int       endian;
}   t_image;
````
And then having a function that creates the image and fills the variables
````c
t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	img;
	
	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels  = mlx_get_data_addr(img.reference, &img.bits_per_pixel, &img.line_size, &img.endian);
	return (img);
}
````

To draw the image on the window, you just have to call ``mlx_put_image_to_window()``. Passing the pointer to the window, the image and the position. The (0,0) coordinates of the window and the images are at the top left corner.
````c
mlx_put_image_to_window(void *window_ptr, void *image_ptr, int x_position, int y_position);
````

---
### Colors
Some functions, like `mlx_pixel_put()` or `mlx_string_put()` will ask you to pass a color as an int. This is referring to the hexadecimal value written like ``0xTTRRGGBB``. You can find the hexadecimal value of a color in any color selector, (search for _colour selector_ on google, it will also give you the RGB values of it). Take care that most of them only give you the hex value for the Red, Green and Blue. So you may need to add the transparency in front of those.
You can generate your own hex colour values using bit shifting. More on that here:
https://harm-smits.github.io/42docs/libs/minilibx/colors.html

And more on images and colours here:
https://github.com/keuhdall/images_example

---
### Sample Program
As I said, the program included in this repository is just a square moving when the arrow keys are pressed.

The program first initializes the mlx and opens a window, saving all data needed in a struct and hooking the function that ends the program to the event that closes the window.

Then creates an image in memory based on a .xpm file and draws it on the window.

Finally, it hooks specific functions to the key-pressed event and the repetition of the loop.
* When a key is pressed, the window is cleared, the position of the sprite is updated based on which of the arrows has been pressed, and it is redrawn in the new position. You can press the keys R, G or B to change the image to a colored square.
* Hooked to the loop is a function that slightly moves the square up and down every 10 frames to make it look animated.

All the code is commented step by step, check it out! ^^^.

---
### Makefile
The Makefile has the following rules:
| make  | |
|-|-|
| all  |  Compiles the code and generates the program _sample.out_ |
| exe |  Compiles and runs the program |
| clean|  Deletes the objects files (*.o) |
| fclean| Makes _clean_ and removes the _sample.out_ file |
| re| Makes _fcleam_ and _all_ again |

---
### References
* https://gontjarow.github.io/MiniLibX/
* https://harm-smits.github.io/42docs/libs/minilibx
* https://github.com/qst0/ft_libgfx
* https://github.com/keuhdall/images_example

miniLibX manuals:
* man /usr/share/man/man3/mlx.1
* man /usr/share/man/man3/mlx_new_window.1
* man /usr/share/man/man3/mlx_pixel_put.1
* man /usr/share/man/man3/mlx_new_image.1
* man /usr/share/man/man3/mlx_loop.1

---
### Contact
Feel free to clone this project, check the code or contact me if you want or find something wrong or missing in this documentation.

Good luck with your projects!
