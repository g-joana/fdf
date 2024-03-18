#include "fdf.h"

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

double	get_edge_width(double edge_size)
{
	double	edge_width;
	double	radians;

	radians = 30.0 * (M_PI / 180.0);
	edge_width = edge_size / cos(radians);

	return (edge_width);
}

// hipotenusa = edge size
// cateto op = edge height
// cateto adj = edge width
// angulo - 30 graus
/*
void	get_edge_size(t_edge *edge)
{
	double radians;

	radians = 30.0 * (M_PI / 180.0);
	edge->size = edge->height / sin(radians);
	// printf("30 * (%f / 180) = %f\n", M_PI, radians);
	// printf("edge->size = %f / %f\n", edge->height, sin(radians));
}
*/
