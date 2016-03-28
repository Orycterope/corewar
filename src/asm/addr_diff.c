/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addr_diff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:19:23 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 17:19:26 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	addr_diff_2_calcul(int i, int cmp, int inst_pos, int *count)
{
	if (i == cmp && *count == 0)
		*count = -1;
	else if (i == inst_pos && *count == 0)
		*count = 1;
	if (i == inst_pos && *count == -1)
		*count = 0;
	else if (i == cmp && *count == 1)
		*count = 0;
}

int		addr_diff_2(t_data *data, int cmp, int inst_pos, int i)
{
	int			count;
	int			diff;
	t_label		*tmp_lbl;
	t_instruc	*tmp_inst;

	count = 0;
	diff = 0;
	tmp_lbl = data->label;
	while (tmp_lbl)
	{
		tmp_inst = tmp_lbl->insts;
		while (tmp_inst)
		{
			addr_diff_2_calcul(i, cmp, inst_pos, &count);
			if (count != 0)
				diff += 1 + get_params_size_ocp(tmp_inst);
			i++;
			tmp_inst = tmp_inst->next;
		}
		tmp_lbl = tmp_lbl->next;
	}
	return (diff);
}

int		addr_diff(t_data *data, char *lbl_name, int inst_pos)
{
	int			i;
	t_label		*tmp_lbl;
	t_instruc	*tmp_inst;

	i = 0;
	tmp_lbl = data->label;
	while (tmp_lbl)
	{
		if (ft_strcmp(tmp_lbl->name, lbl_name) == 0)
			break ;
		tmp_inst = tmp_lbl->insts;
		while (tmp_inst)
		{
			i++;
			tmp_inst = tmp_inst->next;
		}
		tmp_lbl = tmp_lbl->next;
	}
	return (addr_diff_2(data, i, inst_pos, 0));
}
