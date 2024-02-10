/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:30:07 by jgils             #+#    #+#             */
/*   Updated: 2023/11/07 17:44:57 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	ibig;
	size_t	ilit;
	char	*str;

	str = (char *) big;
	if (!(ft_strlen(little)) || big == little)
		return ((char *) big);
	ibig = 0;
	ilit = 0;
	while (big[ibig] && (ibig < len))
	{
		if (big[ibig] == little[0])
		{
			str = &str[ibig];
			ilit = 0;
			while (big[ibig + ilit]
				&& (big[ibig + ilit] == little[ilit]) && (ibig + ilit < len))
				ilit++;
			if (little[ilit++] == '\0')
				return (str);
		}
		ibig++;
	}
	return (NULL);
}
