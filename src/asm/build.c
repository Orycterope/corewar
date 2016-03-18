/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:26:20 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/18 20:48:24 by rporcon          ###   ########.fr       */
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
			ft_printf("->%x\n", tmp_lbl->insts->opcode);
			ft_printf("=>%x<=\n", tmp_lbl->insts->ocp);
			add_to_prog(data, ((unsigned char *)(&tmp_lbl->insts->opcode))[0]);
			add_to_prog(data, ((unsigned char *)(&tmp_lbl->insts->ocp))[0]);
			add_param_to_prog(data, tmp_lbl->insts, tmp_lbl->name);
			tmp_lbl->insts = tmp_lbl->insts->next;
		}
		tmp_lbl = tmp_lbl->next;
	}
	print_prog(data);
}

void	add_param_to_prog(t_data *data, t_instruc *inst, char *lbl_name)
{
	if (inst->param_1 != NULL)
	{
		if (get_ocp(inst->ocp, 0) == 1)
			set_register(data, inst->param_1);
		if (get_ocp(inst->ocp, 0) == 2)
			set_direct(data, inst->param_1, lbl_name, inst);
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

int		addr_diff(t_data *data, int position, t_instruc *inst)
{
	int		diff;

	diff = 0;
	(void)data;
	(void)position;
	(void)inst;
	return (diff);
}

void	set_direct(t_data *data, char *param_1, char *lbl_name,
					t_instruc *inst)
{
	int		val;
	int		i;

	(void)inst;
	if (param_1[1] == LABEL_CHAR)
	{
		val = label_exist(data, param_1 + 2, lbl_name);
	}
	else
	{
		val = ft_atoi(param_1 + 1);
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
