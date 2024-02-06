#include "fdf.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (!validate_map(argv[1]))
			return (1);
		generate_map(argv[1]);
	}
	return (0);
}
