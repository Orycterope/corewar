/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:26:20 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/19 19:12:59 by rporcon          ###   ########.fr       */
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
		ft_printf("{%s}\n", tmp_lbl->name);
		tmp_inst = tmp_lbl->insts;
		while (tmp_inst)
		{
			ft_printf("[%s]\n", tmp_lbl->insts->name); 
//			ft_printf("->%x\n", tmp_lbl->insts->opcode);
//			ft_printf("=>%x<=\n", tmp_lbl->insts->ocp);
			add_to_prog(data, ((unsigned char *)(&tmp_inst->opcode))[0]);
			add_to_prog(data, ((unsigned char *)(&tmp_inst->ocp))[0]);
			add_param_to_prog(data, tmp_inst, tmp_lbl->name, inst_pos);
			tmp_inst = tmp_inst->next;
			inst_pos++;
		}
		tmp_lbl = tmp_lbl->next;
	}
	print_prog(data);
}

void	add_param_to_prog(t_data *data, t_instruc *inst, char *lbl_name,
		int inst_pos)
{
	if (inst->param_1 != NULL)
	{
		if (get_ocp(inst->ocp, 0) == 1)
			set_register(data, inst->param_1);
		if (get_ocp(inst->ocp, 0) == 2)
			set_direct(data, inst->param_1, lbl_name, inst_pos);
//		if (get_ocp(inst->ocp, 0) == 3)
	}
	if (inst->param_2 != NULL)
	{
		if (get_ocp(inst->ocp, 1) == 1)
			set_register(data, inst->param_2);
		if (get_ocp(inst->ocp, 1) == 2)
			set_direct(data, inst->param_2, lbl_name, inst_pos);
//		if (get_ocp(inst->ocp, 0) == 3)
	}
	if (inst->param_3 != NULL)
	{
		if (get_ocp(inst->ocp, 2) == 1)
			set_register(data, inst->param_3);
		if (get_ocp(inst->ocp, 2) == 2)
			set_direct(data, inst->param_3, lbl_name, inst_pos);
//		if (get_ocp(inst->ocp, 0) == 3)
	}
}

int		get_ocp(int ocp, int index)
{
	if (index >= 0 && index <= 3)
	{
		if (index == 0)
			ocp = (ocp >> 6) & 3;
	    if (index == 1)
			ocp = (ocp >> 4) & 3;
	    if (index == 2)
			ocp = (ocp >> 2) & 3;
	    if (index == 3)
			ocp = ocp & 3;
		return (ocp);
	}
	return (-1);
}

int		get_params_size_ocp(int ocp)
{
	return (0);
}

int		addr_diff(t_data *data, char *lbl_name, int inst_pos)
{
	int			i;
	int			count;
	int			diff;
	t_label		*tmp_lbl;
	t_instruc	*tmp_inst;

	i = 0;
	count = 0;
	diff = 0;
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
	i = 0;
	tmp_lbl = data->label;
	while (tmp_lbl)
	{
		tmp_inst = tmp_lbl->insts;
		while (tmp_inst)
		{
			if (i == inst_pos)
			{
				ft_printf("{.->%s<-.}\n", tmp_inst->name);
				count = 1;
			}
			if (count == 1)
			{
				diff += 1;
			}
			i++;
			tmp_inst = tmp_inst->next;
		}
		tmp_lbl = tmp_lbl->next;
	}
	return (0);
}

void	set_direct(t_data *data, char *param, char *lbl_name,
					int inst_pos)
{
	int		val;
	int		i;

	if (param[1] == LABEL_CHAR)
	{
		ft_printf("{%s}", param);
		val = label_exist(data, param + 2, lbl_name);
		addr_diff(data, param + 2, inst_pos);
	}
	else
	{
		val = ft_atoi(param + 1);
		i = DIR_SIZE - 1;
		if (DIR_SIZE > 4)
			error("REG_SIZE is too high");
		while (i >= 0)
		{
			add_to_prog(data, ((unsigned char *)(&val))[i]);
			i--;
		}
	}
}

int		label_exist(t_data *data, char *param_name, char *lbl_name)
{
	t_label		*tmp_lbl;
	int			error;
	int			position;

	tmp_lbl = data->label;
	error = 1;
	position = -1;
	while (tmp_lbl)
	{
		if (ft_strcmp(param_name, tmp_lbl->name) == 0)
			error = 0;
		if (ft_strcmp(lbl_name, tmp_lbl->name) == 0 && error == 1)
			position = 1;
		tmp_lbl = tmp_lbl->next;
	}
	if (error == 1)
		error_str(NULL, "Label name doesn't exist : ", param_name);
	return (position);
}

void	set_register(t_data *data, char *param_1)
{
	int		reg_val;
	int		i;

	reg_val = ft_atoi(param_1 + 1);
	i = REG_SIZE - 1;
	if (REG_SIZE > 4)
		error("REG_SIZE is too high");
	while (i >= 0)
	{
		add_to_prog(data, ((unsigned char *)(&reg_val))[i]);
		i--;
	}
}
