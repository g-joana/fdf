/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:53:58 by jgils             #+#    #+#             */
/*   Updated: 2024/04/18 14:50:21 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>

# ifndef EDGE_SIZE
#  define EDGE_SIZE 42
# endif

# ifndef WIN_WIDTH
#  define WIN_WIDTH 900.0
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 600.0
# endif

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_dot
{
	double	x;
	double	y;
}			t_dot;

typedef struct s_edge
{
	double	height;
	double	width;
	double	size;
}			t_edge;

typedef struct s_map
{
	int		rows;
	int		columns;
	int		**z;
	int		highest_z;
	int		lowest_z;
}			t_map;

typedef struct s_fdf
{
	int		rows;
	int		columns;
	t_dot	**dots;

	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	*map;
}			t_fdf;

int			validate(char *file);
void		free_z(int rows, int **z);
void		free_dots(int rows, t_dot **dots);
void		free_split(char **split);
int			get_gnl_len(char *file);
int			get_row_len(char *line);
int			get_array_len(char **split);
t_map		*generate_map(char *file);
double		get_edge_width(double edge_size, int degrees);
t_edge		*set_edge(t_map map);
void		set_z_limits(t_map *map);
t_fdf		*set_fdf(t_map map);
void		render_fdf(t_data *img, t_fdf fdf);
int			key_hook(int key, t_fdf *fdf);
int			mouse_hook(t_fdf *fdf);
void		start_mlx(t_fdf *fdf);
int			abs(int value);
t_dot		**malloc_dots(t_map map);
t_map		*malloc_map(char *file);

#endif
