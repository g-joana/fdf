#include "fdf.h"

// offset -> diferenca de espaco

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

int	edge_resize()
{}

void	view_fullsize()
{}

t_vertices 	set_vertices(t_map map)
{
aaaaaaaaaaaaaaaaaaaaaa

}

void	render(t_map map)
{
	int	x;
	int	y;
	int	col;
	int	lin;
	int	countx;
	int	county;

	x = 450; //start
	y = 800;

	col = 0;
	lin = 0;
	// 
	while (countx <= (map->xlen * EDGE_SIZE))
	{
		x++;
		y++;
		my_mlx_pixel_put(&img, WIN_WIDTH, WIN_WIDTH, 0x00FF0000);
		if (x / col == EDGE_SIZE)
		while (
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		col += EDGE_SIZE;
	}
	while (
}

int	main(void)
{
	int	y;
	int	x;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 900, 600, "foda dog");
	img.img = mlx_new_image(mlx, 900, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	map = generate_map("");
	/*
	y = 100;
	x = 100;
	while (x <= 400 && x <= 800)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		//y++;
	}
	*/
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
*/
