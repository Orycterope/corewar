/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_list_fct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:53:16 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/29 10:12:40 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label		*lbl_new_elem(char *name)
{
	t_label		*new_element;

	if ((new_element = (t_label *)malloc(sizeof(t_label))) == NULL)
		error("Malloc error");
	if (new_element != NULL)
	{
		new_element->next = NULL;
		new_element->insts = NULL;
		new_element->name = name;
	}
	return (new_element);
}

void		addend_lbl_lst(t_label **lst, t_label *new_elem)
{
	t_label		*tmp;

	tmp = *lst;
	if (tmp == NULL)
		*lst = new_elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
}

void		print_lbl_lst(t_label *lst)
{
	t_label		*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_putchar('[');
		ft_putstr(tmp->name);
		ft_putstr("] ");
		tmp = tmp->next;
	}
}
