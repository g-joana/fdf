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

//TODO: checar contas
double	get_edge_width(double edge_size)
{
	double	edge_width;
	double	radians;

	radians = 30.0 * (M_PI / 180.0);
	edge_width = edge_size / cos(radians);

	return (edge_width);
}

// define distâncias entre os pontos baseado no tamanho do mapa e janela. retorna em t_edge
t_edge	*set_edge(t_map map)
{
	t_edge *edge;
	int	height_len;
	double	map_width;
	double	map_height;

	height_len = get_height_proportion(map);
	edge = (t_edge *)malloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->height = WIN_HEIGHT / height_len;
	edge->size = edge->height * 2;
	// edge->width = get_edge_width(edge->size);
	edge->width = edge->height * sqrt(3);
	map_width = (map.columns + map.rows) * edge->width;
	if (map_width > WIN_WIDTH)
	{
		map_height = (WIN_HEIGHT * WIN_WIDTH) / map_width;
		map_width = WIN_WIDTH;
		edge->height = map_height / height_len;
		edge->size = edge->height * 2;
		// edge->width = get_edge_width(edge->size);
		edge->width = edge->height * sqrt(3);
	}
	return (edge);
}
// hipotenusa = edge size
// cateto op = edge height
// cateto adj = edge width
// angulo - 30 graus
