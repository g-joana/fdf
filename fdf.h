#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

#ifndef EDGE_SIZE
# define EDGE_SIZE 42
#endif

#ifndef WIN_WIDTH
# define WIN_WIDTH 500
#endif

#ifndef WIN_HEIGHT
# define WIN_HEIGHT 500
#endif

typedef struct	s_dot {
	int	x;
	int	y;
}	t_dot;

typedef struct	s_map {
	int	columns;
	int	rows;
	int	**z;
}	t_map;

typedef struct	s_fdf {
	int	columns;
	int	rows;
	int	**z;
	t_dot	**dots;

	//int	*start_vertice;
	//int	*end_vertice;

	//int	lowest_vol;
	//int	highest_vol;
	int	map_len;

	int	edge_size;
}	t_fdf;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	gnl_len(char *file);
int	count_tab(char *file);
int	*tab_atoi(char **tab, int size);
t_map	*generate_map(char *file);
int	validate(char *file);
void	open_win(int h, int w);
