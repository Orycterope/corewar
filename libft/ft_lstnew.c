/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 21:49:13 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:14:01 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;
	void	*cpy;

	lst = (t_list*)malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->next = NULL;
	if (content == NULL)
	{
		lst->content = NULL;
		lst->content_size = 0;
		return (lst);
	}
	cpy = (void *)malloc(content_size);
	if (cpy == NULL)
		return (NULL);
	lst->content = ft_memcpy(cpy, content, content_size);
	lst->content_size = content_size;
	return (lst);
}
