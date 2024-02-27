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

t_fdf	get_map_height(t_fdf fdf, t_map map)
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
	fdf.map_height = highest_vol - lowest_vol;
	return(fdf);
}

/*
t_fdf	*get_edge_size(t_fdf *fdf)
{
	fdf->map_height
}
*/
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
/*
double	get_proportion(int distance1, int distance2)
{
	double	proportion;
	int	negative;

	negative = 1;
	if (distance1 < 0)
	{
		distance1 *= -1;
		negative = -1;
	}
	if (distance2 < 0)
		distance2 *= -1;

	

	if (distance1 == 0)
		return (0);
	if (distance2 == 0)
		return (1 * negative);




	if (distance1 > distance2)
		proportion = ((double)distance1 / (double)distance2);
		// / pelo > divisor comum?
	else
		proportion = 1;
	return (proportion * negative);
}
*/
double	get_proportion(int distance1, int distance2)
{
	double	proportion;
	int	negative;

	negative = 1;
	if (distance1 < 0)
	{
		distance1 *= -1;
		negative = -1;
	}
	if (distance2 < 0)
		distance2 *= -1;

	

	if (distance1 == 0)
		return (0);
	if (distance2 == 0)
		return (1 * negative);




	if (distance1 < distance2)
		proportion = ((double)distance1 / (double)distance2);
		// / pelo > divisor comum?
	else
		proportion = 1;
	return (proportion * negative);
}

void	render_line(t_data *img, double x, double next_x, double y, double next_y)
{
	int	x_distance;
	int	y_distance;
	double	x_steps;
	double	y_steps;

	x_distance = next_x - x; // if > 0 -> direita
	y_distance = next_y - y; // if > 0 -> baixo
	//
	x_steps = get_proportion(x_distance, y_distance);
	y_steps = get_proportion(y_distance, x_distance);
	//
	while ((x != next_x || y != next_y) && x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		x += x_steps;
		y += y_steps;

	}
}

// t_fdf	*generate_fdf(t_map map)
// {
// 	t_fdf	*fdf;
//
// 	fdf = (t_fdf *)malloc(1 * sizeof(t_fdf));
// 	count_map_len(fdf, map); //precisa de dots
// 	calculate_edge_size(fdf);
// 	set_dots(fdf); // precisa de edge_size
// 	render_fdf(fdf);
// 	return (fdf);
// }

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
*/
int	main(void)
{
	int	y;
	int	x;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map map;

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	//map = generate_map(map);
	// y = 100;
	// x = 100;
	// while (x <= 400 && y <= 400)
	// {
	// 	my_mlx_pixel_put(&img, x, y, 0x00FF0000);
	// 	x++;
	// 	y++;
	render_line(&img, WIN_WIDTH, 0, WIN_HEIGHT, 0);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
