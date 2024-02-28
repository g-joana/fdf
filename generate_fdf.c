#include "fdf.h"

// offset -> diferenca de espaco

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

//	a partir dos dados do mapa, calcula o tamanho da altura (em quantidade de pontos)
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
			// TEST: não sei se essa conta ta certa
			vol = (map.rows - (x - y) + map.z[x][y]) + (map.columns - y);
			if (vol > highest_vol)
				highest_vol = map.z[x][y];
			if (vol < lowest_vol)
				lowest_vol = map.z[x][y];
			y++;
		}
		x++;
	}
	// preciso passar fdf de parâmetro?
	fdf.map_height = highest_vol - lowest_vol;
	return(fdf);
}

//	a partir do tamanho da altura e largura do mapa (em pontos) e altura e largura da janela (em px), calcula o espaçamento entre os pontos (em px)
int	get_edge_size(t_fdf fdf)
{
	int	map_width;
	// int	map_height;
	int	edge_size;

	map_width = fdf.columns + fdf.rows;
	// map_height = fdf.map_height;

	if (map_width > fdf.map_height)
		edge_size = map_width / WIN_WIDTH;
	else
		edge_size = fdf.map_height / WIN_HEIGHT;
	return (edge_size);
}

void 	set_dots_volume(t_fdf *fdf, double edge)
{
	(void) fdf, (void) edge;
	return ;
}

//	a partir do edge_size e do mapa, define o par ordenado de cada ponto do fdf
void	set_dots(t_fdf *fdf)
{
	double	edge;
	// int	start;
	int	row;
	int	col;

	edge = get_edge_size(*fdf);
	// start = (WIN_WIDTH - (fdf->columns + fdf->rows * (edge / 2)) / 2);
	//map_width = fdf->columns + fdf->rows;

	row = 0;
	col = 0;
	//start
	fdf->dots[row][col].x = 0;
	fdf->dots[row][col].y = WIN_HEIGHT - (fdf->columns * (edge / 2));
	while (row++ < fdf->rows)
	{
		while (col++ < fdf->columns)
		{
			fdf->dots[row][col].x = fdf->dots[row][col - 1].x + (edge / 2);
			fdf->dots[row][col].y = fdf->dots[row][col - 1].y - (edge / 2);
		}
		col = 0;
		fdf->dots[row][col].x = fdf->dots[row - 1][col].x + (edge / 2);
		fdf->dots[row][col].y = fdf->dots[row - 1][col].y + (edge / 2);

	}
	set_dots_volume(fdf, edge);
}

//	a partir da distância entre um ponto e outro de cada eixo, calcula e retorna o tamanho a ser incrementado no valor inicial para fazer essa linha;
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
		my_mlx_pixel_put(img, x, y, 0xFF79C6);
		x += x_steps;
		y += y_steps;

	}
}
/*
t_fdf	*generate_fdf(t_map map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(1 * sizeof(t_fdf));
 	calculate_edge_size(fdf);
 	set_dots(fdf); // precisa de edge_size
 	render_fdf(fdf);
 	return (fdf);
}

int	main(void)
{
	//int	y;
	// int	x;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	// t_map map;

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
	render_line(&img, 0, WIN_WIDTH, 0, WIN_HEIGHT);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
*/
