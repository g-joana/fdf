/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jou.42.rio@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:56:32 by jgils             #+#    #+#             */
/*   Updated: 2023/11/09 15:51:26 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_tabsize(char const *s, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	if (s[i] == c)
		i++;
	while (s[i])
	{
		if ((s[i] == c && s[i - 1] != c) || (s[i + 1] == '\0' && s[i] != c))
			size++;
		i++;
	}
	return (size);
}

static int	get_substr_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len])
	{
		if (s[len] == c)
			break ;
		len++;
	}
	return (len);
}

static char	**split_tab(char **split, const char *s, char c)
{
	int	tabsize;
	int	itab;
	int	istart;
	int	slen;

	istart = 0;
	itab = 0;
	tabsize = get_tabsize(s, c);
	while (itab < tabsize && s[istart])
	{
		while (s[istart] == c)
		{
			istart++;
			slen++;
		}
		slen = get_substr_len(&s[istart], c);
		split[itab] = ft_substr(s, istart, slen);
		istart += slen;
		itab++;
	}
	split[itab] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		tabsize;
	char	**tab;

	if (s == NULL)
		return (NULL);
	tabsize = get_tabsize(s, c);
	tab = (char **) malloc ((tabsize + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	split_tab(tab, s, c);
	return (tab);
}
