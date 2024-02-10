#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"

#ifndef BLOCK_SIZE
# define BLOCK_SIZE 20;
#endif

typedef struct	s_map
{
	int	xlen;
	int	ylen;
	int	**z;
}	t_map;

int	gnl_len(char *file);
int	count_tab(char *file);
int	*tab_atoi(char **tab, int size);
t_map	*generate_map(char *file);
int	validate(char *file);
