# miniLibX sample | slucas-s
I developed this sample project to play around with the basic functionalities of the miniLibX, the simple graphics library we use at 42. The final program is no more than a square moving around the screen, but I think all the fundamentals to get started with the mlx library are there: opening a window, creating and drawing images and managing events, hooks and input.

### The basic program
The program first initializes the mlx and opens a window, saving all data needed in a struct and hooking the function that ends the program to the event that closes the window.

Then creates an image in memory based on a .xpm file and draws it on the window.

And finally, hooks specific functions to the key-pressed event and the repetition of the loop. 
When a key is pressed, the window is cleared, the position of the sprite is updated based on which of the arrows has been pressed, and it is redrawn in the new position.
Hooked to the loop is a function that slightly moves the square up and down every 10 frames to make it look animated.

All the code is commented step by step, check it out! ^^^.

### Makefile
The Makefile has the following rules:
| make  | |
|-|-|
| all  |  Compiles the code and generates the program _sample.out_ |
| exe |  Compiles and runs the program |
| clean|  Deletes the _sample.out_ file |
| fclean| Makes _clean_ and removes the object files (*.o) |
| re| Makes _fcleam_ and _all_ again |

### Other references
* https://gontjarow.github.io/MiniLibX/
* https://harm-smits.github.io/42docs/libs/minilibx
* https://github.com/qst0/ft_libgfx#the-graphics-branch
* https://github.com/keuhdall/images_example

miniLibX manuals:
* man /usr/share/man/man3/mlx.1
* man /usr/share/man/man3/mlx_new_window.1
* man /usr/share/man/man3/mlx_pixel_put.1
* man /usr/share/man/man3/mlx_new_image.1
* man /usr/share/man/man3/mlx_loop.1
