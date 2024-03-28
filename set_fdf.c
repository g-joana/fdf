/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:44:07 by jgils             #+#    #+#             */
/*   Updated: 2024/03/28 15:44:07 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_z(t_dot **dots, t_map map, double edge_size)
{
	int	col;
	int	row;

	row = 0;
	col = 0;
	while (row < map.rows)
	{
		col = 0;
		while (col < map.columns)
		{
			dots[row][col].y -= map.z[row][col] * edge_size;
			col++;
		}
		row++;
	}
	return ;
}

t_dot	**malloc_dots(t_map map)
{
	int		count;
	t_dot	**dots;

	count = 0;
	dots = (t_dot **)malloc(map.rows * sizeof(t_dot *));
	if (!dots)
		return (NULL);
	while (count < map.rows)
	{
		dots[count] = (t_dot *)malloc(map.columns * sizeof(t_dot));
		if (!dots[count])
		{
			while (count-- >= 0)
				free(dots[count]);
			free(dots);
			return (NULL);
		}
		count++;
	}
	return (dots);
}

void	set_isometric(t_map map, t_edge edge, t_dot **dots)
{
	int		row;
	int		col;
	double	map_width;

	map_width = (map.columns + map.rows - 2) * edge.width;
	dots[0][0].x = ((WIN_WIDTH - map_width) / 2);
	dots[0][0].y = WIN_HEIGHT - (((abs(map.lowest_z)) * edge.height) + 25.0);
	col = 1;
	row = -1;
	while (++row < map.rows)
	{
		if (row > 0)
		{
			dots[row][0].x = dots[row - 1][0].x + edge.width;
			dots[row][0].y = dots[row - 1][0].y + edge.height;
			col = 1;
		}
		while (col < map.columns)
		{
			dots[row][col].x = dots[row][col - 1].x + edge.width;
			dots[row][col].y = dots[row][col - 1].y - edge.height;
			col++;
		}
	}
	set_z(dots, map, edge.size);
}

t_dot	**set_dots(t_map map, t_edge edge)
{
	t_dot	**dots;

	dots = malloc_dots(map);
	if (!dots)
		return (NULL);
	set_isometric(map, edge, dots);
	return (dots);
}

t_fdf	*set_fdf(t_map map)
{
	t_fdf	*fdf;
	t_edge	*edge;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	edge = set_edge(map);
	if (!edge)
		return (NULL);
	fdf->rows = map.rows;
	fdf->columns = map.columns;
	fdf->dots = set_dots(map, *edge);
	if (!fdf->dots)
		return (NULL);
	free(edge);
	start_mlx(fdf);
	return (fdf);
}
