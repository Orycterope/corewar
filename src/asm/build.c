/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:26:20 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/18 16:43:39 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	build(t_data *data)
{
	t_label		*tmp_lbl;

	tmp_lbl = data->label;
	while (tmp_lbl)
	{
		ft_printf("{%s}\n", tmp_lbl->name);
		while (tmp_lbl->insts)
		{
			ft_printf("[%s]\n", tmp_lbl->insts->name); 
			tmp_lbl->insts = tmp_lbl->insts->next;
		}
		tmp_lbl = tmp_lbl->next;
	}
}
