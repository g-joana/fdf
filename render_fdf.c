#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

//	a partir da distância entre um ponto e outro de cada eixo, calcula e retorna o tamanho a ser incrementado no valor inicial para fazer essa linha;
double	get_steps(double distance1, double distance2)
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

int	line(double dist, double start, double end)
{
	if (dist < 0)
	{
		if (start <= end)
			return (1);
	}
	else if (dist > 0)
	{
		if (start >= end)
			return (1);
	}
	return (0);
}

void	render_line(t_data *img, t_dot start, t_dot end)
{
	double	x_distance;
	double	y_distance;
	double	x_steps;
	double	y_steps;

	x_distance = end.x - start.x; // if > 0 -> direita
	y_distance = end.y - start.y; // if > 0 -> baixo
	x_steps = get_steps(x_distance, y_distance);
	y_steps = get_steps(y_distance, x_distance);
	//
	while (!line(x_distance, start.x, end.x) && !line(y_distance, start.y, end.y)
					&& start.x >= 0 && start.y >= 0 && 
						start.x <= WIN_WIDTH && start.y <= WIN_HEIGHT)
	{
		my_mlx_pixel_put(img, start.x, start.y, 0xFF79C6);
		start.x += x_steps;
		start.y += y_steps;
	}
}

void	render_fdf(t_data *img, t_fdf fdf)
{
	int	row;
	int	col;

	row = 0;
	while (row < fdf.rows)
	{
		col = 0;
		while (col < fdf.columns)
		{
			if(row < (fdf.rows - 1))
				render_line(img, fdf.dots[row][col], fdf.dots[row + 1][col]);
			if (col < (fdf.columns - 1))
				render_line(img, fdf.dots[row][col], fdf.dots[row][col + 1]);
			col++;
		}
		row++;
	}
}
