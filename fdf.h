#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "libft/libft.h"

#ifndef BLOCK_SIZE
# define BLOCK_SIZE 20;
#endif

typedef struct	s_map {
	int	xlen;
	int	ylen;
	int	**z;
}	t_map;

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
