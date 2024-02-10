/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:24:20 by jgils             #+#    #+#             */
/*   Updated: 2023/11/02 15:05:58 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*cpy1;
	char	*cpy2;

	i = 0;
	cpy1 = (char *) s1;
	cpy2 = (char *) s2;
	while (i < n)
	{
		if (cpy1[i] != cpy2[i])
			return ((unsigned char)cpy1[i] - (unsigned char)cpy2[i]);
		i++;
	}
	return (0);
}
