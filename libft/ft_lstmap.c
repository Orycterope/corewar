/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:21:12 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:14:51 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstmap_rec(t_list *lst, t_list *maplst,
		t_list *(*f)(t_list *elem))
{
	if (lst == NULL)
		return ;
	maplst->next = (*f)(lst);
	ft_lstmap_rec(lst->next, maplst->next, f);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*maplst;

	maplst = (*f)(lst);
	ft_lstmap_rec(lst->next, maplst, f);
	return (maplst);
}
