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

void	free_z(int rows, int **z)
{
	int	row;

	row = 0;
	while (row < rows)
	{
		free(z[row]);
		row++;
	}
	free(z);
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
	mlx_key_hook(fdf->mlx_win, key_hook, fdf);
	render_fdf(&fdf->img, *fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	mlx_loop(fdf->mlx);
}

/*
int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_fdf	*fdf;
	t_map	*map;
	t_edge	edge;

	if (argc == 2)
	{
		mlx = mlx_init();

		mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
		img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);


		fdf = (t_fdf *)malloc(sizeof(t_fdf));
		if (validate(argv[1]) == 0)
			return (1);
		map = generate_map(argv[1]);
		if (map == NULL)
			return (1);
		fdf->rows = map->rows;
		fdf->columns = map->columns;
		fdf->dots = set_dots(*fdf, *map, &edge);
		set_dots_volume(fdf, *map, edge);

		render_fdf(&img, *fdf);

		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
	}
}
*/
//math.stackexchange.com/questions/989900/calculate-x-y-z-from-two-specific-degrees-on-a-sphere
//https://www.linearity.io/blog/isometric-design
//https://www.mathematics-monster.com/glossary/right_triangles.html
