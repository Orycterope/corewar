/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 22:32:18 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:41:19 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*maillon;

	if (alst == NULL)
		return ;
	maillon = *alst;
	while (maillon)
	{
		next = maillon->next;
		(*del)(maillon, sizeof(t_list));
		maillon->next = NULL;
		maillon = next;
	}
	*alst = NULL;
	alst = NULL;
}
