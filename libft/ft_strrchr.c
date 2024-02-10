/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:16:56 by jgils             #+#    #+#             */
/*   Updated: 2023/11/01 18:30:02 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	char	*s_cpy;

	i = 0;
	ptr = NULL;
	s_cpy = (char *) s;
	while (s_cpy[i])
	{
		if (s_cpy[i] == c)
			ptr = &s_cpy[i];
		i++;
	}
	if (s_cpy[i] == c)
		ptr = &s_cpy[i];
	return (ptr);
}
