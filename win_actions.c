#include "fdf.h"

void	open_win(int h, int w)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, h, w, "Hello world!");
	mlx_loop(mlx);
	(void) mlx_win;
}
