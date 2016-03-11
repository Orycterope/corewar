/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc_list_fct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 11:15:36 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/11 15:26:59 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_instruc	*inst_new_elem(char *name)
{
	t_instruc	*new_element;

	if ((new_element = (t_instruc *)malloc(sizeof(t_instruc))) == NULL)
		error("Malloc error");
	if (new_element != NULL)
	{
		new_element->next = NULL;
		new_element->name = name;
	}
	return (new_element);
}

void		addend_inst_lst(t_instruc **lst, t_instruc *new_elem)
{
	t_instruc	*tmp;

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

void		print_inst_lst(t_instruc **lst)
{
	t_instruc	*tmp;

	tmp = *lst;
	while (tmp)
	{
		ft_putchar('{');
		ft_putstr(tmp->name);
		ft_putstr("} ");
		tmp = tmp->next;
	}
}
