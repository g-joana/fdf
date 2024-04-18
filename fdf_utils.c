/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:53:52 by jgils             #+#    #+#             */
/*   Updated: 2024/04/18 14:58:09 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
	mlx_key_hook(fdf->mlx_win, key_hook, fdf);
	mlx_hook(fdf->mlx_win, 17, 1L << 17, mouse_hook, fdf);
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

t_map	*malloc_map(char *file)
{
	t_map	*map;

	map = (t_map *)malloc(1 * sizeof(t_map));
	if (!map)
		return (NULL);
	map->rows = get_gnl_len(file);
	if (map->rows == 0)
	{
		free(map);
		ft_putstr_fd("Empty map.\n", 2);
		return (NULL);
	}
	map->z = (int **)malloc(map->rows * sizeof(int *));
	if (!map->z)
	{
		free(map);
		return (NULL);
	}
	return (map);
}
