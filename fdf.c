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

void	destroy_map(t_map *map)
{
	int	row;

	row = 0;
	while (row < rows)
	{
		free(map->z[row]);
		row++;
	}
	free(map->z);
	free(map);
}

void	free_dots(int rows, t_dot **dots)
{
	int	row;

	row = 0;
	while (row < rows)
	{
		free(dots[row]);
		row++;
	}
	free(dots);
}

int	key_hook(int key, t_fdf *fdf)
{
	if (key == 65307)
	{
		mlx_destroy_image(fdf->mlx, fdf->img.img);
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		mlx_destroy_display(fdf->mlx);
		free_dots(fdf->rows, fdf->dots);
		free(fdf->mlx);
		free(fdf);
		exit(1);
	}
	return (0);
}

int	mouse_hook(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	mlx_destroy_display(fdf->mlx);
	free_dots(fdf->rows, fdf->dots);
	free(fdf->mlx);
	free(fdf);
	exit(1);
	return (0);
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
	start_mlx(fdf);
	destroy_map(map);
	render_fdf(&fdf->img, *fdf);
	free_dots(fdf->rows, fdf->dots);
	free(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	mlx_loop(fdf->mlx);
}
