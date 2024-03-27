#include "fdf.h"

void	free_z(int rows, int **z)
{
	int	row;

	row = 0;
	while (row < rows)
	{
		free(z[row]);
		row++;
	}
	free(z);
}

void	free_dots(int rows, t_dot **dots)
{
	int	row;

	row = 0;
	while (row < rows)
	{
		free(dots[row]);
		row++;
	}
	free(dots);
}
int	key_hook(int key, t_fdf *fdf)
{
	if (key == 65307)
	{
		mlx_destroy_image(fdf->mlx, fdf->img.img);
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		mlx_destroy_display(fdf->mlx);
		free_dots(fdf->rows, fdf->dots);
		free(fdf->mlx);
		free(fdf);
		exit(1);
	}
	return (0);
}

int	mouse_hook(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	mlx_destroy_display(fdf->mlx);
	free_dots(fdf->rows, fdf->dots);
	free(fdf->mlx);
	free(fdf);
	exit(1);
	return (0);
}
