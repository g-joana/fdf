/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:37:16 by jgils             #+#    #+#             */
/*   Updated: 2023/11/03 11:27:50 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	idst;
	size_t	isrc;

	idst = ft_strlen(dst);
	if (size < idst)
		return (ft_strlen(src) + size);
	isrc = 0;
	while (src[isrc] && (idst + isrc) < (size - 1))
	{
		dst[idst + isrc] = src[isrc];
		isrc++;
	}
	if (idst < size)
		dst[idst + isrc] = '\0';
	return (ft_strlen(src) + idst);
}
