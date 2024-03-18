#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"
#include <math.h>

#ifndef EDGE_SIZE
# define EDGE_SIZE 42
#endif

#ifndef WIN_WIDTH
# define WIN_WIDTH 900.0
#endif

#ifndef WIN_HEIGHT
# define WIN_HEIGHT 600.0
#endif

typedef struct	s_dot {
	double	x;
	double	y;
}	t_dot;

typedef struct	s_edge {
	double	height;
	double	width;
	double	size;
}	t_edge;

typedef struct	s_map {
	int	rows;
	int	columns;
	int	**z;
}	t_map;

typedef struct	s_fdf {
	int	rows;
	int	columns;
	t_dot	**dots;
}	t_fdf;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//generate_map.c
int	validate(char *file);
int	gnl_len(char *file);
int	get_row_len(char *line);
int	*array_atoi(char **tab, int size);
t_map	*generate_map(char *file);
//get_values.c
int	get_height_proportion(t_map map);
double	get_edge_width(double edge_size);
double	get_edge_height(t_map *map);
//set_fdf.c
t_dot	**set_dots(t_fdf fdf, t_map map, t_edge edge);
void 	set_dots_volume(t_fdf *fdf, t_map map, double edge_size);
t_fdf	*set_fdf(t_map map);
//render_fdf.c
double	get_steps(double distance1, double distance2);
int	line(double dist, double start, double end, char axis);
void	render_line(t_data *img, t_dot start, t_dot end);
void	render_fdf(t_data *img, t_fdf fdf);
//window_actions.c
void	open_win(int h, int w);
//test.c
void	print_tab(t_map *map);
