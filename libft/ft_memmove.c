/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:16:43 by jgils             #+#    #+#             */
/*   Updated: 2023/11/01 17:30:16 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*src_cpy;
	char	*dest_cpy;

	src_cpy = (char *) src;
	dest_cpy = (char *) dest;
	if (!dest && !src)
		return (NULL);
	if (src_cpy < dest_cpy)
	{
		i = n - 1;
		while (i >= 0)
		{
			dest_cpy[i] = src_cpy[i];
			i--;
		}
		return (dest);
	}
	i = 0;
	while (i < (int) n)
	{
		dest_cpy[i] = src_cpy[i];
		i++;
	}
	return (dest);
}
