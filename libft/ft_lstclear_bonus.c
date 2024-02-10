/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:04:47 by jgils             #+#    #+#             */
/*   Updated: 2023/11/13 08:23:50 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nxtnode;

	while (*lst)
	{
		nxtnode = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = nxtnode;
	}
	*lst = NULL;
}
