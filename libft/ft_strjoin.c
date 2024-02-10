/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:45:56 by jou               #+#    #+#             */
/*   Updated: 2023/11/08 12:43:24 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*join;

	join = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1 && s1[i])
		{
			join[i] = s1[i];
			i++;
		}
		free (s1);
	}
	while (s2 && *s2)
		join[i++] = *s2++;
	join[i] = '\0';
	if (!join[0])
	{
		free(join);
		return (NULL);
	}
	return (join);
}
