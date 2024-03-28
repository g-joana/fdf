/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:53:44 by jgils             #+#    #+#             */
/*   Updated: 2024/03/28 16:47:46 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	validate(char *file)
{
	int	fd;

	if (ft_strstr(file, ".fdf") == NULL)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

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

int	main(int argc, char **argv)
{
	t_map	*map;
	t_fdf	*fdf;

	if (argc != 2)
	{
		ft_putstr_fd("Invalid input", 2);
		return (1);
	}
	if (!validate(argv[1]))
	{
		ft_putstr_fd("Invalid file. Exiting.", 2);
		return (1);
	}
	map = generate_map(argv[1]);
	if (map == NULL)
		return (1);
	fdf = set_fdf(*map);
	free_z(map->rows, map->z);
	free(map);
	render_fdf(&fdf->img, *fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	mlx_loop(fdf->mlx);
	return (0);
}
