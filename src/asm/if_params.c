/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:12:47 by rporcon           #+#    #+#             */
/*   Updated: 2016/05/09 13:58:08 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	if_one_param(int i, t_data *data, t_instruc *inst, int *order)
{
	if (g_op[i].param_type[0] == T_DIR)
	{
		if (g_op[i].c1 == 0 && g_op[i].c2 == 1 &&
			without_ocp(inst->trim, data, inst) == 1)
			return ;
		else if (g_op[i].c1 == 0 && g_op[i].c2 == 0 &&
			without_ocp_live(inst->trim, data, inst) == 1)
			return ;
		else if (is_direct(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "Incorrect input parameters");
	}
	else if (g_op[i].param_type[0] == T_REG)
	{
		if (is_register(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "Incorect input parameters");
	}
	else
		error_line(data, "Incorrect input parameters");
}

void	if_two_params(int i, t_data *data, t_instruc *inst, int *order)
{
	if (*order == 0)
		two_params_first(i, data, inst, order);
	else if (*order == 1)
		two_params_second(i, data, inst, order);
}

void	two_params_first(int i, t_data *data, t_instruc *inst, int *order)
{
	if (g_op[i].param_type[*order] == (T_DIR | T_IND))
	{
		if (is_direct(inst->trim, data, inst, order) == 1)
			return ;
		else if (is_indirect(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "Incorrect input parameters");
	}
	else if (g_op[i].param_type[*order] == T_REG)
	{
		if (is_register(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "Incorrect input parameters");
	}
	else
		error_line(data, "Incorrect input parameters");
}

void	two_params_second(int i, t_data *data, t_instruc *inst, int *order)
{
	if (g_op[i].param_type[*order] == T_REG)
	{
		if (is_register(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "Incorrect input parameters");
	}
	else if (g_op[i].param_type[*order] == (T_IND | T_REG))
	{
		if (is_indirect(inst->trim, data, inst, order) == 1)
			return ;
		else if (is_register(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "Incorrect input parameters");
	}
	else
		error_line(data, "Incorrect input parameters");
}
