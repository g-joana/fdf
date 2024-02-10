/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jou <jgils@student.42.rio>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:50:36 by jou               #+#    #+#             */
/*   Updated: 2024/01/13 17:28:43 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_rest(char *next_line)
{
	int		i;
	int		i2;
	int		len;
	char	*rest;

	i = 0;
	while (next_line && next_line[i] && next_line[i] != '\n')
		i++;
	if (!next_line[i])
	{
		free (next_line);
		return (NULL);
	}
	if (next_line && next_line[i] == '\n')
		i++;
	rest = (char *) malloc(ft_strlen(next_line) - i + 1 * sizeof(char));
	if (!rest)
		return (NULL);
	i2 = 0;
	len = ft_strlen(next_line) - i;
	while (next_line && i2 < len)
		rest[i2++] = next_line[i++];
	rest[i2] = '\0';
	free(next_line);
	return (rest);
}

static char	*get_line(char *next_line)
{
	int		i;
	int		i2;
	char	*line;

	i = 0;
	while (next_line && next_line[i])
	{
		if (next_line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line = (char *) malloc(i + 1 * sizeof(char));
	if (!line)
		return (NULL);
	i2 = 0;
	while (next_line && i2 < i)
	{
		line[i2] = next_line[i2];
		i2++;
	}
	line[i2] = '\0';
	return (line);
}

static char	*make_lines(int fd, char *buf)
{
	static char	*next_line = 0;
	char		*line;
	int			bytes;

	bytes = 1;
	while (!ft_strchr(buf, '\n') && (bytes > 0))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (buf);
			return (NULL);
		}
		buf[bytes] = '\0';
		next_line = ft_strjoin(next_line, buf);
	}
	free (buf);
	if (!next_line)
		return (NULL);
	line = get_line(next_line);
	next_line = get_rest(next_line);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	return (make_lines(fd, buf));
}
