#include "fdf.h"

// offset -> diferenca de espaco

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}




void	get_map_size(t_fdf fdf, t_map map)
{
	int	count;
	int	lines;

	count = 0;
	lines = fdf.rows;
	fdf.highest_vol = 0;
	fdf.lowest_vol = 0;

	while (lines > 0)
	{
		//conta pra achar altura do volume

		if (map.z[count] > fdf.highest_vol)
			fdf.highest_vol = map.z[count];
		if (map.z[count] < fdf.lowest_vol)
			fdf.lowest_vol = map.z[count];
		count++;
		lines--;
		if (count == fdf.columns)
			count = 0;
	}
	
	fdf.map_len[0] = fdf.columns * fdf.rows;
	fdf.map_len[1] = fdf.highest_vol - fdf.lowest_vol;
}

void 	set_vertices(t_fdf fdf)
{


	fdf.start_vertice[0] = 0;
	fdf.start_vertice[1] = WIN_HEIGHT

}

void	set_dots(t_fdf fdf)
{
	int	row;
	int	column;

	row = 0;
	
	//calcular a partir dos vertices, as distâncias!
	while (row < fdf.rows)
	{
		column = 0;
		while (column < fdf.columns)
		{
			fdf.dots[row][0] = 
			fdf.dots[row
		}
		row++; 



}



void	render_base_line(t_fdf fdf, t_data img)
{
	int	x;
	int	y;
	int	line;
	int	select;
	int	dots;

	x = 450; //start
	y = 800;

	while (line < fdf.rows)
	{
		select = 0;
		x = fdf.dots[select][0];
		y = fdf.dots[select][1];
		select = fdf.columns - 1;
		if (x > fdf.dots[select][0] && y > fdf.dots[select][0])
		while (x <= fdf.dots[select][0] && y >= fdf.dots[select][1])
		{
			
		}
		line++;
	}
	
	
	



	while (countx <= (fdf.columns * fdf.edge_size))
	{
		x++;
		y++;
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		if (x / col == EDGE_SIZE)
		while ()
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		col += EDGE_SIZE;
	}
}
/*
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
	
	generate_map(map);
	y = 100;
	x = 100;
	while (x <= 400 && y <= 400)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
*/
