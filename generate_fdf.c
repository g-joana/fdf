#include "fdf.h"

void print_dots(t_fdf *fdf)
{
	int	count1;
	int	count2;

	count1 = 0;
	while (count1 < fdf->rows)
	{
		count2 = 0;
		while (count2 < fdf->columns)
		{
			// printf("dot.x: %f | dot.y: %f\n", fdf->dots[count1][count2].x, fdf->dots[count1][count2].y);
			count2++;
		}
		printf("\n");
		count1++;
	}
}

int	main(int argc, char **argv)
{
	//int	y;
	// int	x;
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

		//map = generate_map(map);
		// y = 100;
		// x = 100;
		// while (x <= 400 && y <= 400)
		// {
		// 	my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		// 	x++;
		// 	y++;

		fdf = (t_fdf *)malloc(sizeof(t_fdf));
		if (validate(argv[1]) == 0)
			return (1);
		map = generate_map(argv[1]);
		if (map == NULL)
			return (1);
		fdf->rows = map->rows;
		fdf->columns = map->columns;
		// print_tab(map);
		//	generate fdf
		fdf->dots = set_dots(*fdf, *map, &edge);
		set_dots_volume(fdf, *map, edge);
		// print_dots(fdf);
		// printf("start1.x: %f \nstart1.y: %f\n", fdf->dots[0][0].x, fdf->dots[0][0].y);

		render_fdf(&img, *fdf);

		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
	}
}

//math.stackexchange.com/questions/989900/calculate-x-y-z-from-two-specific-degrees-on-a-sphere
//https://www.linearity.io/blog/isometric-design
//https://www.mathematics-monster.com/glossary/right_triangles.html
