#include "fdf.h"

void	open_win(int height, int width)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, height, width, "FDF");

	//mlx_loop_hook(mlx, render_next_frame, YourStruct);

	mlx_loop(mlx);
	(void) mlx_win;
}
