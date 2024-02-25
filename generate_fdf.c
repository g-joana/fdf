#include "fdf.h"

// offset -> diferenca de espaco

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

// 
// 

t_fdf	count_map_len(t_fdf fdf, t_map map)
{
	int	y;
	int	x;
	int	highest_vol;
	int	lowest_vol;
	int	vol;

	highest_vol = 0;
	lowest_vol = 0;
	x = 0;
	while (x < map.rows)
	{
		y = 0;
		while (y < map.columns)
		{
			vol = (map.rows - (x - y) + map.z[x][y]) + (map.columns - y);
			if (vol > highest_vol)
				highest_vol = map.z[x][y];
			if (vol < lowest_vol)
				lowest_vol = map.z[x][y];
			y++;
		}
		x++;
	}
	fdf.map_len = highest_vol - lowest_vol;
	return(fdf);
}

t_fdf	*calculate_edge_size(t_fdf *fdf)
{
	fdf->map_len
}

void 	set_dots_volume(t_fdf *fdf)
{
}

void	set_dots(t_fdf *fdf) // (coloca os pontos da base)
{
	// precisa do edge size
	int	start;
	int	row;
	int	col;

	fdf->edge_size = // IMPORTANTE !! PENSAR EM COMO CALCULAR ESSE
	row = 0;
	col = 0;
	//start
	fdf->dots[row][col].x = 0;
	fdf->dots[row][col].y = WIN_HEIGHT - (fdf->columns * (fdf->edge_size / 2));
	while (row++ < fdf->rows)
	{
		while (col++ < fdf->columns)
		{
			fdf->dots[row][col].x = fdf->dots[row][col - 1].x + 1 * (fdf->edge_size / 2);
			fdf->dots[row][col].y = fdf->dots[row][col - 1].y - 1 * (fdf->edge_size / 2);
		}
		col = 0;
		fdf->dots[row][col].x = fdf->dots[row - 1][col].x + 1 * (fdf->edge_size / 2);
		fdf->dots[row][col].y = fdf->dots[row - 1][col].y + 1 * (fdf->edge_size / 2);

	}
	set_dots_volume(fdf);
}

void	render_line(int x, int y, int next_x, int next_y)
{
	int	x_distance;
	int	y_distance;

	x_distance = x - next_x;
	y_distance = y - next_y;
	//
	//
	if (x_distance == y_distance)
	if (x < next_x && y < next_y)
	while (x <= next_x && y <= next_y)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		y++;
	}
	//
	//
	if (x_distance < 0)
	else if (x_distance > 0)
	else
	if (y_distance < 0)
	else if (y_distance > 0)
	else
	
	(x - next_x) * (y - next_y);
}

t_fdf	*generate_fdf(t_map map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(1 * sizeof(t_fdf));
	count_map_len(fdf, map); //precisa de dots
	calculate_edge_size(fdf);
	set_dots(fdf); // precisa de edge_size
	render_fdf(fdf);
	return (fdf);
}

/*
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
