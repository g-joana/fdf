#include "fdf.h"

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
	y = -1;
	while (++y < map.rows)
	{
		x = 0;
		while (x < map.columns)
		{
			vol = (map.z[y][x] * 3) + x - y;
			if (vol > highest_h)
				highest_h = vol;
			if (vol < lowest_h)
				lowest_h = vol;
			x++;
		}
		vol = -y;
	}
	return (highest_h - lowest_h);
}

double	get_edge_width(double edge_size, int degrees)
{
	double	edge_width;

	edge_width = edge_size * cos(degrees * (M_PI / 180.0));
	return (edge_width);
}

/*
   60
e   .              edge_size
d   |   .         (2 * edge_h)
g   |         .
e   |               .
-   |_                    .
h   |_|____________________(___. 30
   90         edge_w
*/

t_edge	*set_edge(t_map map)
{
	t_edge	*edge;
	int		height_len;
	double	map_width;
	double	map_height;

	height_len = get_height_proportion(map);
	edge = (t_edge *)malloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->height = WIN_HEIGHT / height_len;
	edge->size = edge->height * 3;
	edge->width = get_edge_width(edge->height * 2, 30.0);
	map_width = (map.columns + map.rows) * edge->width;
	if (map_width > WIN_WIDTH)
	{
		map_height = (WIN_HEIGHT * WIN_WIDTH) / map_width;
		map_width = WIN_WIDTH;
		edge->height = map_height / height_len;
		edge->size = edge->height * 3;
		edge->width = get_edge_width(edge->height * 2, 30.0);
	}
	return (edge);
}
