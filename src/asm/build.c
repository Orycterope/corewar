/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:09:47 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 14:14:32 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	build(t_data *data)
{
	t_label		*tmp_lbl;
	t_instruc	*tmp_inst;
	int			inst_pos;

	tmp_lbl = data->label;
	inst_pos = 0;
	while (tmp_lbl)
	{
		tmp_inst = tmp_lbl->insts;
		while (tmp_inst)
		{
			add_to_prog(data, ((unsigned char *)(&tmp_inst->opcode))[0]);
			if (tmp_inst->ocp > 0)
				add_to_prog(data, ((unsigned char *)(&tmp_inst->ocp))[0]);
			add_param_to_prog(data, tmp_inst, tmp_lbl->name, inst_pos);
			tmp_inst = tmp_inst->next;
			inst_pos++;
		}
		tmp_lbl = tmp_lbl->next;
	}
}

void	add_param_to_prog_3(t_data *data, t_instruc *inst, char *lbl_name,
		int inst_pos)
{
	int		ind;

	ind = 0;
	if (ft_strcmp(inst->name, "sti") == 0 ||
			ft_strcmp(inst->name, "lldi") == 0 ||
			ft_strcmp(inst->name, "ldi") == 0)
		ind = 1;
	if (inst->param_3 != NULL)
	{
		if (get_ocp(inst->ocp, 2) == 1)
			set_register(data, inst->param_3);
		else if (ind == 0 && get_ocp(inst->ocp, 2) == 2)
			set_direct(data, inst->param_3, lbl_name, inst_pos);
		else if (get_ocp(inst->ocp, 2) == 3)
			set_indirect(data, inst->param_3, lbl_name, inst_pos);
		else if (ind == 1)
			set_address(data, inst->param_3, lbl_name, inst_pos);
	}
}

void	add_param_to_prog_2(t_data *data, t_instruc *inst, char *lbl_name,
															int inst_pos)
{
	int		ind;

	ind = 0;
	if (ft_strcmp(inst->name, "sti") == 0 ||
			ft_strcmp(inst->name, "lldi") == 0 ||
			ft_strcmp(inst->name, "ldi") == 0)
		ind = 1;
	if (inst->param_2 != NULL)
	{
		if (get_ocp(inst->ocp, 1) == 1)
			set_register(data, inst->param_2);
		else if (ind == 0 && get_ocp(inst->ocp, 1) == 2)
			set_direct(data, inst->param_2, lbl_name, inst_pos);
		else if (get_ocp(inst->ocp, 1) == 3)
			set_indirect(data, inst->param_2, lbl_name, inst_pos);
		else if (ind == 1)
			set_address(data, inst->param_2, lbl_name, inst_pos);
	}
	add_param_to_prog_3(data, inst, lbl_name, inst_pos);
}

void	add_param_to_prog(t_data *data, t_instruc *inst, char *lbl_name,
															int inst_pos)
{
	int		ind;

	ind = 0;
	if (ft_strcmp(inst->name, "sti") == 0 ||
			ft_strcmp(inst->name, "lldi") == 0 ||
			ft_strcmp(inst->name, "ldi") == 0)
		ind = 1;
	if (inst->param_1 != NULL)
	{
		if (inst->ocp == -4)
			set_live(data, inst->param_1, lbl_name, inst_pos);
		else if (inst->ocp == -2)
			set_special(data, inst->param_1, lbl_name, inst_pos);
		else if (get_ocp(inst->ocp, 0) == 1)
			set_register(data, inst->param_1);
		else if (ind == 0 && get_ocp(inst->ocp, 0) == 2)
			set_direct(data, inst->param_1, lbl_name, inst_pos);
		else if (get_ocp(inst->ocp, 0) == 3)
			set_indirect(data, inst->param_1, lbl_name, inst_pos);
		else if (ind == 1)
			set_address(data, inst->param_1, lbl_name, inst_pos);
	}
	add_param_to_prog_2(data, inst, lbl_name, inst_pos);
}

int		label_exist(t_data *data, char *param_name, char *lbl_name)
{
	t_label		*tmp_lbl;
	int			position;

	tmp_lbl = data->label;
	position = -1;
	while (tmp_lbl)
	{
		if (ft_strcmp(param_name, tmp_lbl->name) == 0)
			return (position);
		if (ft_strcmp(lbl_name, tmp_lbl->name) == 0)
			position = 1;
		tmp_lbl = tmp_lbl->next;
	}
	error_str(NULL, "Label name doesn't exist : ", param_name);
	return (-999999999);
}
