#include "fdf.h"
#include <math.h>

void print_dots(t_fdf *fdf)
{
	int	count1;
	int	count2;

	count1 = 0;
	while (count1 < fdf->rows)
	{
		count2 = 0;
		while (count2 < fdf->columns)
		{
			printf("dot.x: %f | dot.y: %f\n", fdf->dots[count1][count2].x, fdf->dots[count1][count2].y);
			count2++;
		}
		printf("\n");
		count1++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

//	calcula  (em quantidade de edge_h)
int	get_height_proportion(t_map map)
{
	int	y;
	int	x;
	int	highest_h;
	int	lowest_h;
	int	vol;

	highest_h = map.columns;
	lowest_h = -map.rows;
	vol = 0;
	y = 0;
	while (y < map.rows)
	{
		x = 0;
		while (x < map.columns)
		{
			//TEST:
			vol = (map.z[y][x] * 2) + x - y;
			// cada edge da base tem h de altura e cada edge vertical tem 2h de altura.
			// cada vez que o x aumenta, o volume aumenta junto.
			// aumentar: aumentar seria subir(-) na tela(eixo y), pois sua origem mudaria.
			// por fim, o volume sobreescreve o volume inicial (so a base) contando com os relevos, caso tenha algum que passe essa altura
			if (vol > highest_h)
				highest_h = vol;
			if (vol < lowest_h)
				lowest_h = vol;
			x++;
		}
		y++;
		vol = -y;
	}
	return (highest_h - lowest_h);
}

//TEST:
double	get_edge_height(t_map *map)
{	
	double	edge_h;
	int	height_len;
	double	proportion;

	height_len = get_height_proportion(*map);
	edge_h = WIN_HEIGHT / height_len;
	map->width = sqrt(pow((map->columns * (edge_h * 2)), 2) + pow((map->rows * (edge_h * 2)), 2)); 
		//raiz de (map.columns * edge_size) ao 2 + (map.rows * edge_size) ao 2;
	if (map->width > WIN_WIDTH)
	{
		proportion = map->width / WIN_WIDTH;
		map->width = map->width / proportion;
		map->new_height = WIN_HEIGHT / proportion;
		edge_h = map->new_height / height_len;
	}
	return (edge_h);
}

// hipotenusa = edge size
// cateto op = edge height
// cateto adj = edge width
// angulo - 30 graus
//TEST:
void	get_edge_size(t_edge *edge)
{
	double radians;

	radians = 30.0 * (M_PI / 180.0);
	edge->size = edge->height / sin(radians);
	printf("30 * (%f / 180) = %f\n", M_PI, radians);
	printf("edge->size = %f / %f\n", edge->height, sin(radians));
}
void	get_edge_width(t_edge *edge)
{
	int	radians;

	radians = 30 * (M_PI / 180);
	edge->width = edge->size / cos(radians);
}
/*

void 	set_dots_volume(t_fdf *fdf, double edge)
{
	(void) fdf, (void) edge;
	return ;
}
*/
//	a partir do edge_size e do mapa, define o par ordenado de cada ponto do fdf
t_dot	**set_dots(t_fdf fdf, t_map map)
{
	int	count;
	t_edge	edge;
	// int	start;
	int	row;
	int	col;
	t_dot	**dots;
	
	//TEST:
	edge.height = get_edge_height(&map);
	get_edge_size(&edge);
	get_edge_width(&edge);
	// start = (WIN_WIDTH - (fdf->columns + fdf->rows * (edge / 2)) / 2);
	//map_width = fdf->columns + fdf->rows;
	count = 0;
	dots = (t_dot **)malloc(fdf.rows * sizeof(t_dot *));
	while (count < fdf.rows)
	{
		dots[count] = (t_dot *)malloc(fdf.columns * sizeof(t_dot));
		count++;
	}
	row = 0;
	col = 0;
	//start
	dots[row][col].x = (WIN_WIDTH - map.width) / 2;
	dots[row][col].y = WIN_HEIGHT - (fdf.rows * edge.height);
	// printf("fdf.rows: %i\n", fdf.rows);
	// printf("fdf.columns: %i\n", fdf.columns);
	// printf("edge: %f\n", edge);
	printf("dots[row][col].x: %f\n", dots[row][col].x);
	printf("dots[row][col].y: %f\n", dots[row][col].y);
	printf("\n\n");
	col++;
	//FIX: primeira linha gigante
	while (row < fdf.rows)
	{
		if (row > 0)
		{
			col = 0;
			dots[row][col].x = dots[row - 1][col].x + edge.width;
			dots[row][col].y = dots[row - 1][col].y + edge.height;
			printf("new row dots[%i][%i].x: %f\n", row, col, dots[row][col].x);
			printf("edge width: %f\n", edge.width);
			//printf("new row dots[%i][%i].y: %f\n", row, col, dots[row][col].y);
			col++;
		}
		while (col < fdf.columns)
		{
			dots[row][col].x = dots[row][col - 1].x + edge.width;
			dots[row][col].y = dots[row][col - 1].y - edge.height;
			//printf("col dots[%i][%i].x: %f\n", row, col, dots[row][col].x);
			//printf("col dots[%i][%i].y: %f\n", row, col, dots[row][col].y);
			col++;
		}
		row++;
	}
	// printf("rows: %i\n", row);
	// printf("columns: %i\n", col);
	//set_dots_volume(fdf, edge);
	return (dots);
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

	// printf("sx %f\nex %f\n\nsy %f\ney %f\n\n\n\n", start.x, end.x, start.y, end.y);
	x_distance = end.x - start.x; // if > 0 -> direita
	y_distance = end.y - start.y; // if > 0 -> baixo
	// printf("psx %f\npex %f\n\npsy %f\npey %f\n\n\n\n", start.x, end.x, start.y, end.y);
	//
	//printf("Pre x_start: %f | pre y_start: %f | pre x_end: %f | pre y_end: %f\n", start.x, start.y, end.x, end.y);
	x_steps = get_proportion(x_distance, y_distance);
	y_steps = get_proportion(y_distance, x_distance);
	//printf("x_start: %f | y_start: %f | x_end: %f | y_end: %f\n\n", start.x, start.y, end.x, end.y);
	// printf("x_steps: %f | y_steps: %f\n", x_steps, y_steps);
	// printf("end.x: %f | end.y: %f\n", end.x, end.y);
	// FIX:PROBLEMA DAS LINHAS NAO TERMINAREM ESTA AQUI!!!!!!!!!!
	// ESSE != GERA COM QUE START.X != X_STEPS NAO CAIA EXATAMENTE EM END.X
	//
	//(start.x != end.x || start.y != end.y)
	while (start.x >= 0 && start.x <= WIN_WIDTH && start.y >= 0 && start.y <= WIN_HEIGHT)
	{
		if ((end.x < 0) && (end.y < 0))
		{
			if (start.x <= end.x)
				break ;
		}
		else if (end.x > 0)
		{
			if (start.x >= end.x)
				break ;
		}
		if (end.y < 0)
		{
			if (start.y <= end.y)
				break ;
		}
		else if (end.y > 0)
		{
			if (start.y >= end.y)
				break ;
		}
		printf("PRE: x entrando: %f | y entrando: %f\n", start.x, start.y);
		my_mlx_pixel_put(img, start.x, start.y, 0xFF79C6);
		start.x += x_steps;
		start.y += y_steps;
		printf("POST: x entrando: %f | y entrando: %f\n", start.x, start.y);

	}
}

void	render_fdf(t_data *img, t_fdf fdf)
{
	int	count;
	int	start;
	int	end;

	count = 0;
	while (count < fdf.rows)
	{
		start = 0;
		end = fdf.columns - 1;
		// printf("fdf.dots[%i][end].x %f\n", count, fdf.dots[count][end].x);
		// printf("fdf.dots[%i][end].y %f\n\n", count, fdf.dots[count][end].y);
		render_line(img, fdf.dots[count][start], fdf.dots[count][end]);
		count++;
	}
	count = 0;
	while (count < fdf.columns)
	{
		start = 0;
		end = fdf.rows - 1;
		render_line(img, fdf.dots[start][count], fdf.dots[end][count]);
		count++;
	}

}


int	main(int argc, char **argv)
{
	//int	y;
	// int	x;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_fdf	*fdf;
	t_map	*map;

	if (argc == 2)
	{
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
		if (validate(argv[1]) == 0)
			return (1);
		map = generate_map(argv[1]);
		if (map == NULL)
			return (1);
		fdf->rows = map->rows;
		fdf->columns = map->columns;
		// printf("rows: %i\ncolumns: %i\n", map->rows, map->columns);
		print_tab(map);
		//	generate fdf
		fdf->dots = set_dots(*fdf, *map);
		print_dots(fdf);
		// printf("start1.x: %f \nstart1.y: %f\n", fdf->dots[0][0].x, fdf->dots[0][0].y);

		render_fdf(&img, *fdf);


		render_line(&img, fdf->dots[0][0], fdf->dots[0][1]);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
	}
}
