#include "fdf.h"

void	set_z_limits(t_map *map)
{
	int	y;
	int	x;
	int	vol;

	map->highest_z = map->columns - 1;
	map->lowest_z = -(map->rows - 1);
	vol = 0;
	y = -1;
	while (++y < map->rows)
	{
		x = 0;
		while (x < map->columns)
		{
			vol = (map->z[y][x] * 3) + x - y;
			if (vol > map->highest_z)
				map->highest_z = vol;
			if (vol < map->lowest_z)
				map->lowest_z = vol;
			x++;
		}
		vol = -y;
	}
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

	height_len = map.highest_z - map.lowest_z;
	edge = (t_edge *)malloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->height = (WIN_HEIGHT - 50.0) / height_len;
	edge->size = edge->height * 3;
	edge->width = get_edge_width(edge->height * 2, 30.0);
	map_width = ((map.columns + map.rows) * edge->width);
	if (map_width > (WIN_WIDTH - 50.0))
	{
		map_height = (((WIN_HEIGHT - 50.0) * (WIN_WIDTH - 50.0)) / map_width);
		map_width = WIN_WIDTH - 50.0;
		edge->height = map_height / height_len;
		edge->size = edge->height * 3;
		edge->width = get_edge_width(edge->height * 2, 30.0);
	}
	return (edge);
}
