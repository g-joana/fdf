#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

//	a partir dos dados do mapa, calcula o tamanho da altura (em quantidade de pontos)
int	get_map_height(t_map map)
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
	return (highest_vol - lowest_vol);
}

//	a partir do tamanho da altura e largura do mapa (em pontos) e altura e largura da janela (em px), calcula o espaçamento entre os pontos (em px)
int	get_edge_size(t_map map)
{
	int	map_width;
	int	map_height;
	int	edge_size;

	map_width = map.columns + map.rows;
	map_height = get_map_height(map);

	if (map_width > map_height)
		edge_size = map_width / WIN_WIDTH;
	else
		edge_size = map_height / WIN_HEIGHT;
	return (edge_size);
}
/*
void 	set_dots_volume(t_fdf *fdf, double edge)
{
	(void) fdf, (void) edge;
	return ;
}
*/
//	a partir do edge_size e do mapa, define o par ordenado de cada ponto do fdf
void	set_dots(t_fdf *fdf, t_map map)
{
	double	edge;
	// int	start;
	int	row;
	int	col;

	//edge = 20;
	edge = get_edge_size(map);
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
	//set_dots_volume(fdf, edge);
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

void	render_line(t_data *img, t_dot start, t_dot end)
{
	int	x_distance;
	int	y_distance;
	double	x_steps;
	double	y_steps;

	x_distance = start.x - end.x; // if > 0 -> direita
	y_distance = start.y - end.y; // if > 0 -> baixo
	//
	x_steps = get_proportion(x_distance, y_distance);
	y_steps = get_proportion(y_distance, x_distance);
	//
	while ((start.x != end.x || start.y != end.y) && start.x >= 0 && start.x <= WIN_WIDTH && start.y >= 0 && start.y <= WIN_HEIGHT)
	{
		my_mlx_pixel_put(img, start.x, start.y, 0xFF79C6);
		start.y += x_steps;
		start.y += y_steps;

	}
}

void	render_fdf(t_data *img, t_fdf *fdf)
{
	int	dots;
	int	count;
	int	start;
	int	end;

	dots = fdf->rows * fdf->columns;
	while (count < dots)
	{
		start = count;
		end = count + fdf->columns;
		render_line(img, *fdf->dots[start], *fdf->dots[end]);
		count = end++;
	}
	count = 0;
	dots = fdf->columns;
	while (count < dots)
	{
		start = count;
		end = count + (fdf->columns * (fdf->rows - 1));
		render_line(img, *fdf->dots[start], *fdf->dots[end]);
		count++;
	}

}

int	main(void)
{
	//int	y;
	// int	x;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_fdf	fdf;
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
	
	fdf = (t_fdf *)malloc(sizeof(t_fdf));

	set_dots(fdf, map);
	render_fdf(fdf);



	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
