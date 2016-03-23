/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 17:36:36 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/23 10:49:29 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_inst_lbl(t_label *lbl)
{
	t_label		*tmp_lbl;
	t_label		*lbl_free;
	t_instruc	*inst_free;

	tmp_lbl = lbl;
	while (tmp_lbl)
	{
		while (tmp_lbl->insts)
		{
			free_inst_lbl_cut(tmp_lbl);
			inst_free = tmp_lbl->insts;
			tmp_lbl->insts = tmp_lbl->insts->next;
			free(inst_free);
		}
		if (tmp_lbl->name != NULL)
			free(tmp_lbl->name);
		lbl_free = tmp_lbl;
		tmp_lbl = tmp_lbl->next;
		free(lbl_free);
	}
}

void	free_inst_lbl_cut(t_label *tmp_lbl)
{
	if (tmp_lbl->insts->name != NULL)
		free(tmp_lbl->insts->name);
	if (tmp_lbl->insts->param_1 != NULL)
		free(tmp_lbl->insts->param_1);
	if (tmp_lbl->insts->param_2 != NULL)
		free(tmp_lbl->insts->param_2);
	if (tmp_lbl->insts->param_3 != NULL)
		free(tmp_lbl->insts->param_3);
	if (tmp_lbl->insts->trim != NULL)
		free(tmp_lbl->insts->trim);
}
