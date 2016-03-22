/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:09:47 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/22 17:46:38 by jriallan         ###   ########.fr       */
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

void	set_indirect(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[0] == LABEL_CHAR)
	{
		val = label_exist(data, param + 1, lbl_name);
		val = val * addr_diff(data, param + 1, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
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

int		get_params_size_ocp_2(int ret, int i, int *arr, t_instruc *inst)
{
	if (ft_strcmp(inst->name, "live") != 0 &&
			ft_strcmp(inst->name, "zjump") != 0 &&
			ft_strcmp(inst->name, "fork") != 0 &&
			ft_strcmp(inst->name, "lfork") != 0)
		ret++;
	while (i < 4)
	{
		if (arr[i] == REG_CODE)
		{
			ret += 1;
		}
		if (arr[i] == DIR_CODE)
		{
			if (ft_strcmp(inst->name, "sti") == 0 ||
					ft_strcmp(inst->name, "lldi") == 0 ||
					ft_strcmp(inst->name, "ldi") == 0)
				ret += 2;
			else
				ret += 4;
		}
		if (arr[i] == IND_CODE)
			ret += 2;
		i++;
	}
	return (ret);
}

int		get_params_size_ocp(t_instruc *inst)
{
	int		arr[4];

	arr[0] = get_ocp(inst->ocp, 0);
	arr[1] = get_ocp(inst->ocp, 1);
	arr[2] = get_ocp(inst->ocp, 2);
	arr[3] = get_ocp(inst->ocp, 3);
	if (inst->ocp == -4)
		return (4);
	if (inst->ocp == -2)
		return (2);
	return (get_params_size_ocp_2(0, 0, arr, inst));
}

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

void	set_address(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[1] == LABEL_CHAR)
	{
		val = label_exist(data, param + 2, lbl_name);
		val = val * addr_diff(data, param + 2, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param + 1);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
}

void	set_live(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[1] == LABEL_CHAR)
	{
		val = label_exist(data, param + 2, lbl_name);
		val = val * addr_diff(data, param + 2, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[3]);
		add_to_prog(data, ((unsigned char *)(&val))[2]);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param + 1);
		add_to_prog(data, ((unsigned char *)(&val))[3]);
		add_to_prog(data, ((unsigned char *)(&val))[2]);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
}

void	set_special(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[1] == LABEL_CHAR)
	{
		val = label_exist(data, param + 2, lbl_name);
		val = val * addr_diff(data, param + 2, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param + 1);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
}

void	set_direct(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[1] == LABEL_CHAR)
	{
		val = label_exist(data, param + 2, lbl_name);
		val = val * addr_diff(data, param + 2, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[3]);
		add_to_prog(data, ((unsigned char *)(&val))[2]);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param + 1);
		add_to_prog(data, ((unsigned char *)(&val))[3]);
		add_to_prog(data, ((unsigned char *)(&val))[2]);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
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

void	set_register(t_data *data, char *param_1)
{
	int		reg_val;

	reg_val = ft_atoi(param_1 + 1);
	add_to_prog(data, ((unsigned char *)(&reg_val))[0]);
}
