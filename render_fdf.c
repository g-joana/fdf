/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:54:16 by jgils             #+#    #+#             */
/*   Updated: 2024/04/18 15:32:46 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

double	get_steps(double distance1, double distance2)
{
	double	proportion;
	int		negative;

	negative = 1;
	if (distance1 == 0)
		return (0);
	else if (distance1 < 0)
	{
		distance1 *= -1;
		negative = -1;
	}
	if (distance2 < 0)
		distance2 *= -1;
	else if (distance2 == 0)
		return (1 * negative);
	if (distance1 < distance2)
		proportion = ((double)distance1 / (double)distance2);
	else
		proportion = 1;
	return (proportion * negative);
}

int	line(double dist, double start, double end, char axis)
{
	if ((axis == 'x' && start > WIN_WIDTH) || (axis == 'y'
			&& start > WIN_HEIGHT))
		return (1);
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

	x_distance = end.x - start.x;
	y_distance = end.y - start.y;
	x_steps = get_steps(x_distance, y_distance);
	y_steps = get_steps(y_distance, x_distance);
	while (!line(x_distance, start.x, end.x, 'x') && !line(y_distance, start.y,
			end.y, 'y'))
	{
		my_mlx_pixel_put(img, start.x, start.y, 0x48E448);
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
			if (row < (fdf.rows - 1))
				render_line(img, fdf.dots[row][col], fdf.dots[row + 1][col]);
			if (col < (fdf.columns - 1))
				render_line(img, fdf.dots[row][col], fdf.dots[row][col + 1]);
			col++;
		}
		row++;
	}
}
