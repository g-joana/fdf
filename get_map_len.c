/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:54:08 by jgils             #+#    #+#             */
/*   Updated: 2024/03/27 18:54:08 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_gnl_len(char *file)
{
	int		fd;
	int		len;
	char	*line;

	len = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

int	get_row_len(char *line)
{
	int	len;
	int	number;

	len = 0;
	number = 0;
	while (line[len] && line[len] != '\n' && line[len] != '\0')
	{
		while (line[len] == ' ')
			len++;
		if (line[len] == '\0' || line[len] == '\n')
			break ;
		while (line[len] != ' ')
		{
			if (line[len + 1] == '\0' || line[len + 1] == '\n' || line[len
					+ 1] == ' ')
			{
				len++;
				number++;
				break ;
			}
			len++;
		}
	}
	return (number);
}

int	get_array_len(char **split)
{
	int	len;

	len = 0;
	while (split && split[len])
	{
		if (split[len][0] == '\n' || split[len][0] == '\0')
			break ;
		len++;
	}
	return (len);
}
