#include "fdf.h"

// offset -> diferenca de espaco

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	int	y;
	int	x;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 900, 600, "Hello world!");
	img.img = mlx_new_image(mlx, 900, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	y = 100;
	x = 100;
	while (y <= 400 && x <= 800)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
